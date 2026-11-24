# =============================================================================
# joints.asm - Joint table accessor routines
#
# Purpose : Routines for reading/writing the joint table defined in
#           scorpion.asm (current angle, target angle, min, max per joint).
# Owner   : MIPS team
# C ref   : reference/joints.c (hand-translated, not compiler output)
# Run     : Not run on its own. Assembled together with scorpion.asm
#           (MARS "assemble all files in directory" or .include).
# =============================================================================

# TODO: get_current  - return current angle of joint
# TODO: set_current  - set current angle of joint
# TODO: get_target   - return target angle of joint
# TODO: set_target   - set target angle of joint
# TODO: get_min      - return min angle of joint
# TODO: get_max      - return max angle of joint
# TODO: clamp        - clamp an angle to a joint's min/max
#
# TODO: document calling convention for each (joint id / value registers)
