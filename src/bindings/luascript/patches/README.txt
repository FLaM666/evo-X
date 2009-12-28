----------------------------------------------------------------------------------------
PATCH : patch_hack_for_loadscripts.txt  

RESULT: Apply this if you want to be able to use 
.loadscripts gm command, else if you use it server 
may/will crash ( NOTE . you cant use it from CLI as it will 
crash your server )

WHY: The reason this command crashes is that your script exports AI`s
If some script exports AI and there is spawned creature that has scuh AI
then server will crash on .loadscripts commands .The reason is that mangos
tryes to address memory in the dll ,which is reloaded actually this memory dont exist
This is core bug in mangos that is also valid for EVERY other scripting library you use

----------------------------------------------------------------------------------------