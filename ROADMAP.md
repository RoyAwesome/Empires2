Roadmap
==========

If you feel that you can take one of these items, Clone the repo, add it, then submit it as a pull request.  



Code
-------

* Create a Damage system (I started but only have raw damage).  [Here is where the code is](https://github.com/RoyAwesome/Empires2/blob/master/Source/Empires2/Public/BaseEmpiresWeapon.h#L11), and Epic has a pretty decent [overview of damage](https://www.unrealengine.com/blog/damage-in-ue4).  This is a creative system.  You get to decide if you want resistances and how they are stored, as well as if you want physics based damage or just raw hit stuff.  
* Loadout/Inventory system.  I was going to do this but it someone wants to tackle it I can play with vehicles.
* ~~Create slots for the 'Draw Weapon' and 'Put Away Weapon' animations.  This is actually super straightforward and the code for that is [Here](https://github.com/RoyAwesome/Empires2/blob/master/Source/Empires2/Public/BaseEmpiresWeapon.h#L50) and [Here](https://github.com/RoyAwesome/Empires2/blob/master/Source/Empires2/Private/Empires2Character.cpp#L157)~~ **[Done](https://github.com/RoyAwesome/Empires2/commit/f000b91bff59d3e1c04a7bead16fb05d83a3683e)**
* Add recoil patterns.  I have an idea for this, modelled after Planetside 2.  
* Add Jump/Crouch States
* Add Aim Down Sights
* Firemode system (eg: Single Shot, 3 round burst, full auto) (create a designer centric way of doing this, so that new firemodes can be created in the editor)

Design
---------

* Hook up the Starter Animation Pack and prototype character model to the Empires Character
* Create a Main Menu level [with UMG](https://docs.unrealengine.com/latest/INT/Engine/UMG/UserGuide/index.html)
* Create a simple HUD with UMG


Art
------------
* Port the SrcEmpires View Models and animations to UE4
* Port the SrcEmpires Player Models and retarget the animations to the Starter Pack
* Port the 3rd person weapon models to UE4.  


