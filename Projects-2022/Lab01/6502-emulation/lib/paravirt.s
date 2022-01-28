;
; Oliver Schmidt, 2013-05-16
;
; int open (const char* name, int flags, ...);
; int __fastcall__ close (int fd);
; int __fastcall__ read (int fd, void* buf, unsigned count);
; int __fastcall__ write (int fd, const void* buf, unsigned count);
; int __fastcall__ break (...);
; int __fastcall__ dump (...);
;
        .export         args, exit, _open, _close, _read, _write, _break, _dump

;args            := $FFF0
;exit            := $FFF1
;_open           := $FFF2
;_close          := $FFF3
;_read           := $FFF4
;_write          := $FFF5
;_break          := $FFF6
;_dump           := $FFF7

.segment "CODE"

.macro make_vmc name, callnum
	name:
		.byte $80, callnum
		rts
.endmacro

make_vmc args,   $00
make_vmc exit,   $01
make_vmc _open,  $02
make_vmc _close, $03
make_vmc _read,  $04
make_vmc _write, $05
make_vmc _break, $06
make_vmc _dump,  $07

; define further VM CALLs here
