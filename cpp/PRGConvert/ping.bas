10 HIRES 0,15
20 DESIGN 0,2048+49152
30 @..BBBBBB................
40 @.B......B...............
50 @B........B..............
60 @B........B..............
70 @B........B..............
80 @B........B..............
90 @B........B..............
100 @.B......B...............
110 @..BBBBBB................
120 @........................
130 @........................
140 @........................
150 @........................
160 @........................
170 @........................
180 @........................
190 @........................
200 @........................
210 @........................
220 @........................
230 @........................
240 MOB SET 0,32,8,0,0
250 DESIGN 0,2048+49152+64
260 @BBBBBBBBBBBBBBBBBBBBBBBB
270 @BBBBBBBBBBBBBBBBBBBBBBBB
280 @BBBBBBBBBBBBBBBBBBBBBBBB
290 @BBBBBBBBBBBBBBBBBBBBBBBB
300 @........................
310 @........................
320 @........................
330 @........................
340 @........................
350 @........................
360 @........................
370 @........................
380 @........................
390 @........................
400 @........................
410 @........................
420 @........................
430 @........................
440 @........................
450 @........................
460 @........................
470 MOB SET 1,33,8,0,0
475 MOB SET 2,33,8,0,0
480 DETECT 0
490 X=160:Y=100:DX=5+RND(0):DY=4+RND(0):P1=160:P2=160
500 MMOB 0,X+24,Y+50,X+24,Y+50,0,1
510 MMOB 1,P1+24,148,P1+24,148,0,1
515 MMOB 2,P2+24,148,P2+24,148,0,1
520 DETECT 0
530 CO=1-CHECK(0,0)
540 IF CO=1 THEN DY=-DY
550 X=X+DX:Y=Y+DY
560 IF X<0 OR X>=313 THEN X=X-DX:DX=-DX
570 IF Y<0 THEN 671
580 IF Y>205 THEN 673
590 GOSUB 2000
600 IF P1 < 0 THEN P1=0
610 IF P1 > 296 THEN P1=296
620 IF P2 < 0 THEN P2=0
630 IF P2 > 296 THEN P2=296
640 RLOCMOB 0,X+24,Y+50,0,1
650 RLOCMOB 1,P2+24,246,0,1
655 RLOCMOB 2,P1+24,50,0,1
660 IF CO=1 THEN DETECT 0
670 GOTO 520
671 PRINT "PLAYER TWO WON"
672 GOTO 680
673 PRINT "PLAYER ONE WON"
680 MOB OFF 0
690 MOB OFF 1
700 END
2000 REM JOY
2010 J1=NOT PEEK(56321)
2020 J2=NOT PEEK(56320)
2030 IF J1 AND 4 THEN P1=P1-10
2040 IF J1 AND 8 THEN P1=P1+10
2050 IF J2 AND 4 THEN P2=P2-10
2060 IF J2 AND 8 THEN P2=P2+10
2070 RETURN
