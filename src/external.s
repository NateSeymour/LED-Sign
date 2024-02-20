.section .rodata
.global display_images

image_test:
.incbin "../src/assets/test.gif"

display_images:
.word image_test
