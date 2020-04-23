#!/usr/bin/env escript
%%! -smp enable -sname mmcshadow -mnesia debug verbose[/color]
main([String]) ->
  io:format("args ~p~n",[String]);
main([Str1,Str2]) ->
  io:format("two args ~p ~p~n",[Str1,Str2]);
main([Str1,Str2,Str3]) ->
  io:format("three args ~p ~p ~p ~p~n",[Str1,Str2,Str3,node()]);
main(_) ->
  io:format("zero args~n").

