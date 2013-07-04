require 'mkmf'

def bits
	  ['bits'].pack('p').size * 8
end

library_dir = File.realpath(File.join(File.dirname(__FILE__), '..', '..', 'lib', 'u_are_u', "lib#{bits}"))

dir_config('', 'compare', 'compare')
dir_config('', 'u_are_u', 'u_are_u')
dir_config('', library_dir, library_dir)

have_library('dpfj') or raise
have_library('dpfpdd') or raise
have_library('stdc++') or raise

$objs = ['fingerprint.o', 'compare/compare.o']

create_makefile('keyme/fingerprint')
