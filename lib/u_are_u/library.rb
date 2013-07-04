def bits
	['bits'].pack('p').size * 8
end

$LOAD_PATH << File.join(File.dirname(__FILE__), "lib#{bits}")
