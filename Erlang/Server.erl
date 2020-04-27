#!/usr/bin/env escript

main(_) ->
	% ok 是一个atom类型，在ErLang里，atom只能用于比较是否相同， 内部可能使用整数来代表某个atom
	{ok, Listen} = gen_tcp:listen(2345, [binary, {packet, 4}, {reuseaddr, true}, {active, true}]),
	% {ok, Listen} = gen_tcp:listen(2345, [binary, {packet, 4}, {Ip_to_integer([36,7,227,13]), true}, {active, true}]),
	{ok, Socket} = gen_tcp:accept(Listen),
	{ok,{IP_Address,Port}} = inet:peername(Socket),
	io:format("[~p][~p] ~n", [IP_Address, Port]),
	gen_tcp:close(Socket).

%Ip_to_integer([A,B,C,D]) ->
%	(A*16777216)+(B*65536)+(C*256)+ D. 

%Integer_to_ip=fun(Ip)-> {Ip bsr 24, (Ip band 16711680) bsr 16, (Ip band 65280) bsr 8, Ip band 255} end.