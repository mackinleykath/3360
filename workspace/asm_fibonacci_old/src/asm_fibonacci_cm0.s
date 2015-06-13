 	.syntax unified
 	.cpu cortex-m0
 	.align	2
 	.global	asm_fibonacci
 	.thumb
 	.thumb_func
asm_fibonacci:
  # key:
  # r0 is first parameter, n
  # r1 is return value
  # r2 is frame pointer
  # r3 and r4 are scratch variables (a and b in notes)

  push {r2,r1,lr}
  # only four variables per recurse
  sub sp, #12 
  # save n
  str r0, [r2, #4]
  # Check input for 0, 1, or >20
  cmp r0, #0
  beq end
  cmp r0, #1
  beq end
  cmp r0, #20
  bge end

  # Otherwise
b:
  # a <- n
  ldr r3, [r2, #4] 
  # a - 1
  subs r3, #1       
  # n <- a
  mov r0, r3    
  # this makes f(n-1)   
  bl asm_fibonacci
  # b = f(n-1)
  mov r4, r0        
a:
  # a <- n
  ldr r3, [r2, #4]  
  # a - 2
  subs r3, #2       
  # n <- a
  mov r0, r3
  bl asm_fibonacci 
  # a = f(n-2) 
  mov r3, r0       

  # Finally:
  adds r0, r3, r4
  b end
  

end: # just return n
  mov r1, r0 
  mov sp, r2
  add sp, #12
  pop {r2,r1,pc}
