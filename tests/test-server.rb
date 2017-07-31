#!/usr/bin/env ruby

require 'socket'

server = TCPServer.new(ARGV[0] || 12345)

while client = server.accept
  while msg = client.gets
    client.puts(msg)
  end
  client.close
end

server.close