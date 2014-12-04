Gem::Specification.new do |s|
	s.name        = 'fingerprint-ruby'
	s.version     = '0.0.4'
	s.date        = '2014-12-04'
	s.summary     = 'U.are.U fingerprint scanner methods.'
	s.description = 'Load and verify fingerprints scanned using a U.are.U fingerprint scanner.'
	s.authors     = ['Zachary Salzbank']
	s.email       = 'zach@key.me'

	s.files       = Dir.glob('lib/*.{rb}') +
	                Dir.glob('lib/u_are_u/**/*') +
									Dir.glob('ext/fingerprint/*.{cpp,h,rb}') +
									Dir.glob('ext/fingerprint/u_are_u/*.{h}') +
									Dir.glob('ext/fingerprint/compare/*.{cpp,h}')

	s.extensions  = ['ext/fingerprint/extconf.rb']

	s.homepage    = 'http://github.com/keyme/fingerprint-ruby'
end
