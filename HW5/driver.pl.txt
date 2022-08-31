#!/usr/bin/perl

	system("cp board.txt brd_a");

	$time = 10;
	$result = 5;

	while ($result == 5)
	{
		system("cat brd_a");

		$move = `cat brd_a | ./playerA $time`;
		chop($move);
		$result = `./verifier $move brd_a brd_b`;
		chop($result);

		print "A made move: $move\n";
		
		if ($result == 0)
		{
			die "B won!\n";
		}
		elsif ($result == 1)
	    {
	     	die "Draw!\n";
	    }
		elsif ($result == 2)
	    {
	       	die "A won!\n";		    
	    }

		$move = `cat brd_b | ./playerB $time`;
		chop($move);
		$result = `./verifier $move brd_b brd_a`;
		chop($result);
		
		print "B made move: $move\n";
	        
		if ($result == 0)
	        {
	            	die "A won!\n";
	        }
	        elsif ($result == 1)
	        {
	            	die "Draw!\n";
	        }
	        elsif ($result == 2)
	        {
	            	die "B won!\n";
	        }

	};

