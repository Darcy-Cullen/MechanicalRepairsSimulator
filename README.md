# MechanicalRepairsSimulator

This project was implemented using procedural programming.

This program is used to simulate the process of the mechanical repairs.The “claims.txt” and “mechanics.txt” file saves the information from individual claim and mechanic, respectively.

Each claim (one line record from the “claims.txt”) represents a (car) repairing requirement, while it
attempts to go through mechanics ONLY in its own list. They will try from the first to the last one (one
mechanic for one time) to see if this mechanic could fix the problem (as the trial process). The process
stops if one trial gets successful, otherwise it will go to the next mechanic (for another trial). This claim
fails if no trials (mechanics) are successful in the list, and it will consider as the (car) scrap.


Once the program is compiled into the executable say ABC, it should run something like follows:
$ /ABC claims.txt mechanics.txt output.txt
