# item_packager.rb
#
# This file takes an item JSON, and generates a SHA512 checksum before
# encrypting the original plain-text JSON with a known XOR key.
#
# *.item -> XOR Secure Item JSON Data
# *.sum -> SHA512 Checksum
#
# .sum files are not included in release builds.
#
# The original .json is also not included in releases.
# The script automatically collects and XORs all found
# JSON files in `./items/*.json` 

require 'digest'
require 'fileutils'

# XOR the data with the provided key bytes
def xor_data(data, key_bytes)
  key_len = key_bytes.length
  data.bytes.each_with_index.map do |byte, i|
    (byte ^ key_bytes[i % key_len]).chr
  end.join
end

def hex_string_to_bytes(hex_str)
  hex_str = hex_str.sub(/^0x/i, '')
  [hex_str].pack('H*').bytes
end

# Process each item file: read, encrypt, and write .item and .sum files
def process_file(path, key_bytes)
  base = File.basename(path, '.json')
  dir = File.dirname(path)

  json_data = File.read(path)
  checksum = Digest::SHA512.hexdigest(json_data)
  xored = xor_data(json_data, key_bytes)

  # Write the encrypted data and checksum to .item and .sum
  File.write("#{dir}/#{base}.item", xored)
  File.write("#{dir}/#{base}.sum", checksum)

  puts "Packaged #{base} -> .item, .sum"
end

def main
  puts '%%% ItemPacker for NeonDreams %%%'
  puts 'Remember that the key is in the source!'
  hex_input = '0xA1D4FC33'

  begin
    key_bytes = hex_string_to_bytes(hex_input)
    raise if key_bytes.empty?
  rescue
    puts "Invalid key format. Must be in hex, e.g. 0xDEAD or 5F0F."
    return
  end

  Dir.glob('./items/*.json').each do |json_file|
    process_file(json_file, key_bytes)
  end
end

main