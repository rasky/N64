//================
// 64Drive Include
//================

constant DRIVE64_REG_BASE($B8000000)
constant DRIVE64_REG_STATUS($200)
constant DRIVE64_REG_COMMAND($208)
constant DRIVE64_REG_MAGIC($2EC)

constant DRIVE64_CMD_ENABLE_CARTROM_WRITES($F0)
constant DRIVE64_CMD_DISABLE_CARTROM_WRITES($F1)

macro Drive64WaitReady() {
  li t1,DRIVE64_REG_BASE
{#}WaitReady:
  lhu t0,DRIVE64_REG_STATUS(t1)
  bnez t0,{#}WaitReady
  nop
}

macro Drive64SendCommand(cmd) {
  Drive64WaitReady()

  li t1,DRIVE64_REG_BASE
  li t0,{cmd}
  sw t0,DRIVE64_REG_COMMAND(t1)

  Drive64WaitReady()
}

macro Drive64GrabScreenshot(screen_x, screen_y, bytes_per_pixel) {
  Drive64SendCommand(DRIVE64_CMD_ENABLE_CARTROM_WRITES) // Enable writes to ROM area

  // Use PI DMA to copy the screenshot into cartrom area
  lui a0,PI_BASE
  lui t0,$0010 // Start VRAM Start Offset
  sw t0,PI_DRAM_ADDR(a0)
  lui t1,$1100 // CARTROM upper area
  sw t1,PI_CART_ADDR(a0)
  la t2,$A0100000+(({screen_x}*{screen_y}*{bytes_per_pixel})-4)
  sw t2,PI_RD_LEN(a0)
}
