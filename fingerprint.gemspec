Gem::Specification.new do |s|
	s.name        = 'fingerprint'
	s.version     = '0.0.1'
	s.date        = '2013-07-04'
	s.summary     = 'U.are.U fingerprint scanner methods.'
	s.description = 'Load and verify fingerprints scanned using a U.are.U fingerprint scanner.'
	s.authors     = ['Zachary Salzbank']
	s.email       = 'zach@keyme.net'

	s.files       = Dir.glob('lib/*.{rb}') +
	                Dir.glob('lib/u_are_u/**/*') +
									Dir.glob('ext/fingerprint/*.{cpp,h,rb}') +
									Dir.glob('ext/fingerprint/u_are_u/*.{h}') +
									Dir.glob('ext/fingerprint/compare/*.{cpp,h}')

	s.extensions  = ['ext/fingerprint/extconf.rb']

	s.homepage    = 'http://github.com/keyme/fingerprint-ruby'
end
