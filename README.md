puzzle
======

2014-6-13

   <p>
1. implement basic game rule for 6*6 chess board: when touching screen,player can move a certain chess to desired place
   with swapping chess . And when touch end,  more than three contiguous chess with the same color will be cancelled.
   Then new chess will be generated from top.
   </p>
   <p>
2. install package for Android "ballPuzzle.apk" is at "proj.android/bin" folder.
   executable program for windows is at "proj.win32\Debug.win32" folder.
   </p>
screen shot:
![image](https://github.com/luozhonghai/puzzle/blob/master/screenshot/20140613.jpg)

2014-6-22

   <p>
1. balls which have same color are cancelled by sequence now and makes combos.
  </p>
   <p>
2. implement game round in 60 seconds and calculate scores.
   </p>
   <p>
3. implement basic puzzle server with ROR , send player's score and then update high score after a game round.
   </p>

2014-6-30
   <p>
1. add background image for the game and adjust the position of sprites for different screens, change the size of chess        board to 5*6.
  </p>
   <p>
2. test the connection to server on android emulator successfully.
   </p>
