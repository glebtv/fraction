require File.dirname(__FILE__) + '/ext/fraction'

class Fraction
  attr_reader :numerator, :denominator

  def to_html
    entity = case self.numerator

    when 1 then
      case self.denominator
      when 2 then "&frac12;"
      when 3 then "&#x2153;"
      when 4 then "&frac14;"
      when 5 then "&#x2155;"
      when 6 then "&#x2159;"
      when 8 then "&#x215E;"
      end

    when 2 then
      case self.denominator
      when 3 then "&#x2154;"
      when 5 then "&#x2156;"
      end

    when 3 then
      case self.denominator
      when 4 then "&frac34;"
      when 5 then "&#x2157;"
      when 8 then "&#x215C;"
      end

    when 4 then "&#x2158;"

    when 5 then
      case self.denomiator
      when 6 then "&#x215A;"
      when 8 then "&#x215D;"
      end
      
    when 7 then "&#x215E;"
    end

    entity ||= "#{self.numerator}/#{self.denominator}"
    entity
  end
end
