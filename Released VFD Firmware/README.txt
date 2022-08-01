All steps in this README are shown in the following video:
https://youtu.be/xo_RG4Zgdmc


1: Download and install beta DDcut:
Mac: https://drive.google.com/file/d/1ckqJORKC9LdCiA5aiHUaRxv-CCwtGKTb/view?usp=sharing
Windows: https://drive.google.com/file/d/1EFyPPsjfm5gzKeZ9XufNfWa4SMT3P-wj/view?usp=sharing

2: Open DDcut and go to settings>software

3: Choose the Beta 328p & 32M1 hex files, located in the folder "2022JUN09 beta closed loop" (same directory as this readme).

4: Click "Upload Custom Firmware" button.
DO NOT CLICK THE 'OK' button on the popup message (that says "Upload succeeded == true").   

5: Wait one minute, then click the OK button.

6: Close the settings window, then quit and relaunch DDcut.  This probably isn't necessary, but sometimes I wasn't able to connect to GG without restarting.

7: Open DDcut and go to settings>software.  The 'FW' field should now say '20220609'.

8: Open Manual Control window, then type '$$' to bring up the settings.  Verify the following settings:
-$30 should be 8500
-$31 should be 1360
Please let me know if the old values persist ($30=8000 & $31=0).

9: Home GG, then type:
G0 X0 Y-120
G0 Z-78
M3
S1500

10: Cut existing files and verify everything works well.  Please let me know if you run into problems with any existing code.

11: Cut new things at lower speeds and verify everything works well.

12: If the new closed loop firmware is terrible, you can reload the old version by following the same steps (above), but with the files inside the folder "restore old firmware".

/////////////////////////////////////////////////////

Revision History:

2020MAR03
-Initial open loop release.

*************

2022JUN09
-Internal closed loop protype.

*************

2022JUL27
-Internal closed loop prototype.
-Fixed issue where X Table level routine did not work ($L).

*************

2022JUL31
-Internal closed loop prototype.
-GG can now tell DDcut how close actualRPM is to goalRPM.
Each time a connection to grbl is opened, type 'Mxxx' (TBD, probably 'M105') to enable this "spindle RPM feedback mode".  
Once enabled, grbl will no longer respond with 'ok' after processing each message, but instead will respond:
'0k' if actualRPM is within 0000:0999 of goalRPM (note: this is "number zero + k", not "letter o + k")
'1k' if actualRPM is within 1000:1999 of goalRPM
'2k' if actualRPM is within 2000:2999 of goalRPM
'3k' if actualRPM is beyond 3000      of goalRPM

-Fixed corner case where spindle might not start rotating when commanded to.

*************