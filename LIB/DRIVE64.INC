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
  li a0,DRIVE64_REG_BASE
{#}WaitReady:
  lhu t0,DRIVE64_REG_STATUS(a0)
  bnez t0,{#}WaitReady
  nop
}

macro Drive64SendCommand(cmd) {
  Drive64WaitReady()

  li a0,DRIVE64_REG_BASE
  li t0,{cmd}
  sw t0,DRIVE64_REG_COMMAND(a0)

  Drive64WaitReady()
}

macro Drive64GrabScreenshot(screen_x, screen_y, bytes_per_pixel) {
  Drive64SendCommand(DRIVE64_CMD_ENABLE_CARTROM_WRITES) // Enable writes to ROM area

  lui a0,$A010 // A0 = VRAM Start Offset
  la a1,$A0100000+(({screen_x}*{screen_y}*{bytes_per_pixel})-4) // A1 = VRAM End Offset

  lui a2,$B100 // A2 = CARTROM upper area
{#}CopyScreen:
  lw t0,0(a0)
  nop
  sw t0,0(a2) // Writes are buggy (?); need to writes many times to fix it
  sw t0,0(a2) // TODO: ask marshallh why
  sw t0,0(a2)
  sw t0,0(a2)
  sw t0,0(a2)
  sw t0,0(a2)
  sw t0,0(a2)
  sw t0,0(a2)
  sw t0,0(a2)
  sw t0,0(a2)
  sw t0,0(a2)
  sw t0,0(a2)
  sw t0,0(a2)
  sw t0,0(a2)
  sw t0,0(a2)
  sw t0,0(a2)
  sw t0,0(a2)
  sw t0,0(a2)
  sw t0,0(a2)
  sw t0,0(a2)
  sw t0,0(a2)
  sw t0,0(a2)
  sw t0,0(a2)
  sw t0,0(a2)
  sw t0,0(a2)
  sw t0,0(a2)
  sw t0,0(a2)
  sw t0,0(a2)
  sw t0,0(a2)
  sw t0,0(a2)

  addi a2,4
  bne a0,a1,{#}CopyScreen
  addi a0,4 // Delay Slot
}
