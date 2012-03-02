spec = Gem::Specification.new do |s|
	s.name = 'fraction'
	s.authors = ["Christopher Lord", "David Eppstein", "Arno Formella"]
	s.email = "christopherlord+fractiongem@gmail.com"
	s.homepage = "https://github.com/clord/fraction"
	s.version = '0.3.2'
	s.summary = 'Provides a "to_fraction" method on all ruby floats.'
	s.description = 'Provides "to_fraction" and to_whole_fraction methods on all ruby floats and numerics.'
	s.extensions << 'ext/extconf.rb'
	s.files = %w(ext/fraction.c fraction.rb README.md)
end
