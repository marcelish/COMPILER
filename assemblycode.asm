sys_exit	equ	1
sys_read	equ	3
sys_write	equ	4
stdin		equ	0 ; default keyboard
stdout		equ	1 ; default terminal screen
stderr		equ	3

	section .data

	userMsg		db      'Enter an integer(less than 32,765): '
	lenUserMsg	equ	$-userMsg
	displayMsg	db	'You entered: '
	lenDisplayMsg	equ	$-displayMsg
	newline		db	0xA 	; 0xA 0xD is ASCII <LF><CR>

	Ten             DW      10  ;Used in converting to base ten.

	printTempchar	db	'Tempchar = : '
	lenprintTempchar	equ 	$-printTempchar

	Result          db      'Ans = '
	ResultValue	db	'aaaaa'
	db	0xA
	ResultEnd       equ 	$-Result    ; $=> here, subtract address Result

	num		times 6 db 'ABCDEF'
	numEnd		equ	$-num
	LIT1 DW 1

	section .bss
 
	TempChar        RESB       1              ;temp space for use by GetNextChar
	testchar        RESB       1
	ReadInt         RESW       1              ;Temporary storage GetAnInteger.
	tempint         RESW	   1              ;Used in converting to base ten.
	negflag         RESB       1              ;P=positive, N=negative

	ans resw 1
	N resw 1
	CIN resw 1
	FUNCTIONCALL resw 1
	BURRISFACTORIAL resw 1
	T1 resw 1
	T2 resw 1
	T3 resw 1
	T4 resw 1
	T5 resw 1
	T6 resw 1
	T7 resw 1
	T8 resw 1
	T9 resw 1
	T10 resw 1
	global _start

	section .text

	_start:	nop

		Again:

		call PrintString
		call GetAnInteger
		mov ax, [ReadInt]
		mov [N], ax
		
		call FUNCTIONCALL
		call fini 
		W1: nop
		mov ax, [N]
		cmp ax, [LIT1]
		jle L1
		mov ax, [N]
		sub ax, [LIT1]
		mov [T1], ax
		mov ax, [T1]
		mov [N], ax
		mov ax, [ans]
		mul word [N]
		mov [T1], ax
		mov ax, [T1]
		mov [ans], ax

		mov ax,[ans]
		call ConvertIntegerToString
		mov eax, 4	;write   ; 'Ans = value <newline>
		mov ebx, 1	; default sys_out
		mov ecx, Result   	;start address for print
		mov edx, ResultEnd ;Length to write.
		int 80h

		jmp W1
		L1: nop

		;jmp     Again

	; exit code
fini:
	mov eax,sys_exit ;terminate, sys_exit = 1 
	xor ebx,ebx	      ;zero in ebx indicates success
	int 80h


	; subpgm to print a string
	PrintString:
	push    ax              ;Save registers
	push    dx
	mov eax, 4		;Linux print device register
	mov ebx, 1		; print default output device
	mov ecx, userMsg	; pointer to string
	mov edx, lenUserMsg
	int	80h		; interrupt 80 hex, call kernel
	pop     dx              ;Restore registers
	pop     ax
	ret


	; subpgm to get an integer
	GetAnInteger:
	mov eax,3	;read
	mov ebx,2	;device
	mov ecx, num	;buffer address
	mov edx,6	;max characters
	int 0x80
	mov edx,eax 	; eax contains the number of character read including <lf>
	mov eax, 4
	mov ebx, 1
	mov ecx, num
	int 80h


	; subpgm to convert a string to an integer
	ConvertStringToInteger:
	mov ax,0	;hold integer
	mov [ReadInt],ax ;initialize 16 bit number to zero
	mov ecx,num	;pt - 1st or next digit of number as a string terminated by <lf>
	mov bx,0
	mov bl, byte [ecx] ;contains first or next digit
Next:
	sub bl,'0'	;convert character to number
	mov ax,[ReadInt]
	mov dx,10
	mul dx		;eax = eax * 10
	add ax,bx
	mov [ReadInt], ax
	mov bx,0
	add ecx,1 	;pt = pt + 1
	mov bl, byte[ecx]
	cmp bl,0xA	;is it a <lf>
	jne Next	; get next digit
	ret


	; subpgm to convert an integer to a string
	ConvertIntegerToString:
	mov ebx, ResultValue + 4   ;Store the integer as a five digit char string at Result for printing
ConvertLoop:
	sub dx,dx  ; repeatedly divide dx:ax by 10 to obtain last digit of number
	; to obtain last digit of number
	mov cx,10  ; as the remainder in the DX register.  Quotient in AX.
	div cx
	add dl,'0' ; Add '0' to dl to convert from binary to character.
	mov [ebx], dl
	dec ebx
	cmp ebx,ResultValue
	jge ConvertLoop
	ret

