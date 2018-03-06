require_relative 'cext'

class Vector
  
  attr_reader :x, :y
  
  def initialize(x, y)
    @x = x
    @y = y
  end
  
end

v = Vector.new(100, 200)

puts magnitude(v)

day = date
puts "#{day.year}-#{day.month}-#{day.day}"
