.pc = $0810

main:
	ldx #$0

loopChar:
	lda text,x
	beq endLoop			//Branch at end of string
	sta currentChar

checkNode:
	lda trie
	sta terminal
	lda trie + 1
	sta wordNum
	
loopNode:
	clc
	lda loopNodeChar + 1
	adc #$2
	sta loopNodeChar + 1
	bcc loopNodeChar
checkNodeIncHigh:
	inc loopNodeChar + 2
	
loopNodeChar:
	lda trie
	
	cmp #$3f
	beq notInList
	cmp #$23
	beq notInList
	cmp currentChar
	beq followAddr
	
	
	inc loopNodeChar + 1
	inc loopNodeChar + 1
	inc loopNodeChar + 1

	bne loopNode
	inc trie + 1
	jmp loopNode

followAddr:
	                     
	inx
	jmp loopChar

notInList:
	lda #2
	sta $400
	jmp endLoop
	
inList:
	lda #1
	sta $400
	jmp endLoop
	

endLoop:
	jmp endLoop

text:
	.text "akesi"
	.byte 0
currentChar:
	.byte 0
terminal:
	.byte 0
wordNum:
	.byte 0
	
.pc = $c000 "Trie"
trie:
	.var trieData = LoadBinary("../trie-c000-asciifix.bin")
	.fill trieData.getSize(), trieData.get(i)
	.byte $3f