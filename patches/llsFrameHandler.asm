; 275410 27541b
; This is the frame handler for loadLocaleString
; Originally would have freed a string on the stack (the tmp)
; but since we removed that, we don't want it to do anything

BITS 32

ret