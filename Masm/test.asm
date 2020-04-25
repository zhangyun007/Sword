;示例代码2.asm
;语法：ML64

.486
.model flat

    .data                          ;此为数据区
    sum DWORD 0                    ;定义名为sum的变量
    .code                          ;此为代码区
    WinMain PROC
        mov eax,5                  ;将数字5送入而eax寄存器
        add eax,6                  ;eax寄存器加6
    WinMain ENDP
	
end