BasicUpstart2(start)
	* = $080d

start:
	sei					// Disable interrupts for initialisation

	lda #$7f			// Disable CIA interrupts
	sta $dc0d
	sta $dd0d

	lda $dc0d			// Remove pending CIA interrupts
	lda $dd0d

	lda #$01			// Enable VIC raster interrupt
	sta $d01a

	lda #$40			// Set VIC raster interrupt
	sta $d012

	lda #$10			// Make sure highest bit is still 0
	sta $d011

	lda #<irq1			// Set up interrupt pointer
	sta $0314
	lda #>irq1
	sta $0315

	jsr chars

	cli

loop:
	jmp loop
	
irq1:
	asl $d019			// Clear VIC interrupt condition
	clc

	lda scroll
	sbc #$1
	cmp #$ff
	bne setscroll
movechars:
	clc
	lda charload + 1
	adc #$28
	sta charload + 1
	lda charload + 2
	adc #$0
	sta charload + 2

	jsr chars

	clc
	lda #$7

setscroll:
	sta scroll
	sta $d020
	ora #$10
	sta $d011

	jmp $ea81			// Kernal irq return routine

chars:					// Set registers before copying character data
	ldx #$0
	ldy #$0
	clc
	lda charload + 2
	sta tempvar

charload:
	lda text,x			// Load character data into Accumulator
charstore:
	sta $0400,x			// Save character data

	inx
	bne charload		// After 256 characters have been written, increment
	inc charload + 2	// the addresses by $100
	bne charcont
	inc charload + 1
charcont:
	inc charstore + 2
	iny					// Keep track of how much data has been written
	cpy #$4				// and break the loop after 1000 bytes
	bne charload

	clc
	lda #$04
	sta charstore + 2
	lda tempvar
	sta charload + 2

	rts
	
tempvar:
	.byte $0
scroll:
	.byte $7
text:
	.text "1234567890123456789012345678901234567890"
	.text "                                        "
	.text "                                        "
	.text "                                        "
	.text "                                        "
	.text "                                        "
	.text "                                        "
	.text "                                        "
	.text "                                        "
	.text "                                        "
	.text "                                        "
	.text "                                        "
	.text "                                        "
	.text "                                        "
	.text "                                        "
	.text "                                        "
	.text "                                        "
	.text "                                        "
	.text "                                        "
	.text "                                        "
	.text "                                        "
	.text "                                        "
	.text "                                        "
	.text "                                        "
	.text "         final line                     "
	.text "                                        "
	.text "                                        "
	.text "                                        "
	.text "                                        "
	.text "                                        "
	.text "                                        "
	.text "                                        "
	.text "                                        "
	.text "                                        "
	.text "                                        "
	.text "                                        "
	.text "                                        "
	.text "                                        "
	.text "                                        "
	.text "                                        "
	.text "                                        "
	.text "                                        "
	.text "         more line                     "
	.text "                                        "
