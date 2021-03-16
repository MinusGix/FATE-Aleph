// This file is for helper functions

#include "helper.hpp"
#include "aleph.hpp"
#include "../patches/file.h"
#include <chrono>
#include <cstdio>
#include <iostream>
#include <profileapi.h>
#include <utility>
#include <vector>
#include <map>
#include <winnt.h>

EXTERNAL PRINTF_FUNC void __cdecl aleph_info(const char* text, ...) {
    printf("[Aleph::info]: ");
    va_list args;
    va_start(args, text);
    vprintf(text, args);
}
EXTERNAL PRINTF_FUNC void __cdecl aleph_warn(const char* text, ...) {
    printf("[Aleph::warn]: ");
    va_list args;
    va_start(args, text);
    vprintf(text, args);
}
EXTERNAL PRINTF_FUNC void __cdecl aleph_error(const char* text, ...) {
    printf("[Aleph::error]: ");
    va_list args;
    va_start(args, text);
    vprintf(text, args);
}

/// Really basic hash for string buffers
size_t hash_c_string(const char* p, size_t s) {
    size_t result = 0;
    const size_t prime = 31;
    for (size_t i = 0; i < s; ++i) {
        result = static_cast<uint32_t>(p[i]) + (result * prime);
    }
    return result;
}

#define TIMER_START(x) LARGE_INTEGER li; \
    QueryPerformanceFrequency(&li); \
    double pc_freq = (static_cast<double>(li.QuadPart)) / 1000.0; \
    QueryPerformanceCounter(&li); \
    __int64 x = li.QuadPart
#define TIMER_END(x, t) QueryPerformanceCounter(&li); \
    double t = static_cast<double>(li.QuadPart - x) / pc_freq


/// Temporary structure for keeping track of info about the file.
struct FileInfo {
    std::string name;
    double time_overall;
    uint32_t times_loaded;

    std::map<size_t, int> split_on;
    std::map<char, int> comment_markers;

    FileInfo(std::string name_t, double time_t, uint32_t times_loaded_t) : name(name_t), time_overall(time_t), times_loaded(times_loaded_t) {}

    void add(double time, const char* split, char comment_marker) {
        this->time_overall += time;
        this->times_loaded += 1;

        this->split_on.emplace(hash_c_string(split, strlen(split)), 0).first->second += 1;
        this->comment_markers.emplace(comment_marker, 0).first->second += 1;
    }
};
static std::map<size_t, FileInfo> files;
static double time_overall = 0.0;
static uint32_t times_loaded = 0;

EXTERNAL __cdecl void log_files() {
    for (const auto& entry : files) {
        const FileInfo& file = entry.second;
        const double average_time = file.time_overall / static_cast<double>(file.times_loaded);
        aleph_info("'%s': %fms #%d, avg: %f; diff: split(%d), comment(%d)\n", file.name.c_str(), file.time_overall, file.times_loaded, average_time, file.split_on.size(), file.comment_markers.size());
    }
    aleph_info("Overall took: %fms for #%d file parse calls, avg: %f\n", time_overall, times_loaded, time_overall / static_cast<double>(times_loaded));
}

EXTERNAL CLASS_METHOD void file_parse(File* self, StringPtrDeque* lines, char* split_on, char comment_marker) {
    const char* path_data = h_string_data(&self->path);
    const size_t hash = hash_c_string(path_data, self->path.length);
    if (files.count(hash) == 0) {
        files.emplace(hash, FileInfo(std::string(path_data, self->path.length), 0.0, 0));
    }
    times_loaded++;


    TIMER_START(counter_start);

    // Currently basic reimplementation of the original code.
    FILE* file = self->file;

    if (file == nullptr || is_file_eof(file)) {
        return;
    }

    string tmp;
    h_string_clear(&tmp);
    // string_expand_v(&tmp, 4096, 0);

    const char* content = nullptr;
    do {
        file_readline_v(self, &tmp);
        content = h_string_data(&tmp);
    } while (content[0] == comment_marker);

    // If there is still data
    if (!self->eof) {
        uint32_t index = string_find(&tmp, &comment_marker, 0, 1);
        if (index != 0xffffffff) {
            string_erase(&tmp, index, 0xffffffff);
            // Not sure what the point of this is
            // string_insert(&tmp, &tmp, 0, 0xffffffff);
        }

        char* split_on_end = split_on;
        char cur_chr;
        do {
            cur_chr = *split_on_end;
            split_on_end = split_on_end + 1;
        } while (cur_chr != '\0');
        const uint32_t split_on_length = static_cast<uint32_t>(split_on_end - (split_on + 1));

        index = string_find_first_of(&tmp, split_on, 0, split_on_length);

        string data;
        h_string_clear(&data);
        while (index != 0xffffffff) {
            h_string_empty(&data);
            uint32_t start = string_find_first_of1(&tmp, split_on, index, split_on_length);
            string_copy_into(&tmp, &data, index, start - index);
            string_ptr_deque_push_back(lines, &data);
            index = string_find_first_of(&tmp, split_on, start, split_on_length);
        }

        h_string_free(&data);
    }
    h_string_free(&tmp);


    TIMER_END(counter_start, time);
    files.at(hash).add(time, split_on, comment_marker);
    time_overall += time;
    // if (time >= 0.1) {
    //     aleph_info("File parse: '%s'\n", h_string_data(&self->path));
    //     aleph_info("\t%fms\n", time);
    // }
    // string tmp;
    // h_string_clear(&tmp);

    // char* content = nullptr;

    // if (self->file != nullptr && !is_file_eof(self->file)) {
    //     // This seems to discard all lines that start with the comment marker
    //     do {
    //         file_readline_v(self, &tmp);
    //         // string_insert(&tmp, &line, 0, 0xffffffff);
    //         // h_string_free(&line);
    //         // h_string_clear(&line);

    //         content = h_string_data(&tmp);
    //     } while (content[0] == comment_marker);

    //     // If there is still data
    //     if (!self->eof) {
    //         uint32_t index = string_find(&tmp, &comment_marker, 0, 1);
    //         if (index != 0xffffffff) {
    //             string_erase(&tmp, index, 0xffffffff);
    //             // Not sure what the point of this is
    //             // string_insert(&tmp, &tmp, 0, 0xffffffff);
    //         }

    //         char* split_on_end = split_on;
    //         char cur_chr;
    //         do {
    //             cur_chr = *split_on_end;
    //             split_on_end = split_on_end + 1;
    //         } while (cur_chr != '\0');
    //         const uint32_t split_on_length = static_cast<uint32_t>(split_on_end - (split_on + 1));

    //         index = string_find_first_of(&tmp, split_on, 0, split_on_length);

    //         string data;
    //         h_string_clear(&data);
    //         while (index != 0xffffffff) {
    //             h_string_empty(&data);
    //             uint32_t start = string_find_first_of1(&tmp, split_on, index, split_on_length);
    //             string_copy_into(&tmp, &data, index, start - index);
    //             string_ptr_deque_push_back(lines, &data);
    //             index = string_find_first_of(&tmp, split_on, start, split_on_length);
    //         }

    //         h_string_free(&data);
    //     }
    //     h_string_free(&tmp);
    // }
}


// TODO: We could improve this be getting the file lock
// and calling the underlying functions (that assume file lock)
// and then releasing it.
// Not sure how much of an improvement that would be.
// But even better would be to lock in the file that calls this.

/// This function does one less string allocation and copy.
/// Minor.
EXTERNAL CLASS_METHOD string* file_readline(File* self, string* output) {
    h_string_clear(output);
    // Preallocate a certain string size that should be enough for most lines.
    string_expand_v(output, 128, 0);

    FILE* file = self->file;
    if (file == nullptr) {
        self->eof = true;
        return output;
    }
    while (!is_file_eof(file)) {
        uint32_t value;
        const uint32_t count_read = fread_v(&value, 1, 1, file);
        if (count_read != 1 && is_file_eof(file)) {
            self->eof = true;
        }
        const char ch = static_cast<char>(value);
        if (ch == '\0' || ch == '\n') {
            break;
        }
        string_append_copies_of_single(output, 1, ch);
    }

    if (is_file_eof(file)) {
        self->eof = true;
    }

    return output;
}