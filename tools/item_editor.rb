# item_editor.rb
#
# A CLI tool for creating item JSON files that comply to
# the NeonDreams JSON Item Schema. This tool is a development
# tool for Neon Dreams, and is not intended for external use.
#
# Scheme:
#
# {
#   "item_id":
#   {
#     "name": "",
#     "desc": "",
#     "type": "",
#     "attributes" : ""
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

def collect_attributes
  puts "Enter attributes one at a time. Type '!' to finish:"
  attributes = []

  loop do
    print "  Attribute: "
    input = gets.chomp
    break if input == '!'
    exit if input.downcase == 'q'
    attributes << input unless input.empty?
  end

  attributes
end

def create_item
  item_id = prompt("Item ID")
  name = prompt("Name")
  desc = prompt("Description")
  type = prompt("Type")
  attributes = collect_attributes

  {
    item_id => {
      "name" => name,
      "desc" => desc,
      "type" => type,
      "attributes" => attributes
    }
  }
end

def main
  puts '%%% ItemEditor for NeonDreams %%%'
  FileUtils.mkdir_p('./items')

  loop do
    puts "\n--- Create a New Item ---"
    item_data = create_item
    item_id = item_data.keys.first
    name = item_data[item_id]["name"]

    file_path = "./items/#{name.downcase.strip.gsub(/\s+/, "_")}.json"
    File.open(file_path, 'w') do |file|
      file.write(JSON.pretty_generate(item_data))
    end

    puts "Item '#{name}' saved to #{file_path}"
  end
end

main