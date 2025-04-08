# item_packager.rb
#
# This file takes the npc JSON, secures it with a SHA512
# checksum, then secures it with XOR. Both the resulting
# XOR'd file and the key are dumped to two files.
#
# *.npc -> XOR Secure Item JSON Data
# *.sum -> SHA512 Checksum
#
# .sum files are not included in release builds.
# The original .json is also not included with the release builds.

def main()
  puts '%%% NPCPacker for NeonDreams %%%'
end

main()