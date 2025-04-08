# npc_editor.rb
#
# A CLI tool for creating NPC JSON files that comply with
# the NeonDreams JSON NPC Schema. This tool is a development
# tool for Neon Dreams, and is not intended for external use.
#
# {
#   "npc_id": {
#     "name": "",
#     "type": "",
#     "texture": "",
#     "dialogue": [
#       "..."
#     ]
#   }
# }

require 'json'
require 'fileutils'

def prompt(field)
  print "#{field} (or 'q' to quit): "
  input = gets.chomp
  exit if input.downcase == 'q'
  input
end

def dialogue_input
  puts "Enter dialogue lines one at a time. Type '!' to finish:"
  lines = []

  loop do
    print "  Line: "
    input = gets.chomp
    break if input == '!'
    exit if input.downcase == 'q'
    lines << input unless input.empty?
  end

  lines
end

def create_npc
  npc_id = prompt("NPC ID")
  name = prompt("Name")
  type = prompt("Type")
  texture = prompt("Texture")
  dialogue = dialogue_input

  {
    npc_id => {
      "name" => name,
      "type" => type,
      "texture" => texture,
      "dialogue" => dialogue
    }
  }
end

def save_npc_to_file(npc_data)
  FileUtils.mkdir_p("npc")
  file_path = "npc/#{npc_data.keys.first}.json"
  File.open(file_path, 'w') do |file|
    file.write(JSON.pretty_generate(npc_data))
  end
  puts "Saved to #{file_path}"
end

def main
  puts '%%% NPCEditor for NeonDreams %%%'
  npc = create_npc
  save_npc_to_file(npc)
end

main
