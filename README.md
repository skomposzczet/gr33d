# gr33d - greed but offensive

## Description:

Welcome to gr33d, game inspired by unix game greed. Goal of the game is to clear as much of screen as possible. Your position is marked with '@'. You can move using 'wsadqezc' (you can also use arrows).
    
                              q w e   N N N
                               \|/     \|/
                              a-@-d   N-@-N
                               /|\	   /|\
                              z s c	  N N N

You move eating N squares, where N is first number in direction you choose to go. You can't move if move will get you out of board or will cross already blank space. You can press 'h' to toogle highlighting possible ways or 'l' to quit. Good luck and have fun! Psst watch out for game host, he can be mean sometimes!

## Command line options:

    --name <un>
			sets username to un
	--highlight==false
			toogles highlighting off
	-s
			prints top scores
	help
			prints help page
		
## Installing
Clone the project then:
```
            $ cd gr33d
            $ mkdir build
            $ cd build
            $ cmake ..
            $ sudo make install
```
			
## Files:

&nbsp; ~/.gr33d/ <br>
&nbsp; Default location for gr33d files
		
## Authors:

skomposzczet (https://github.com/skomposzczet).
