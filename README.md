# G4Project_Pacman  
How to push?  
1. cd into directory (Desktop)  
2. cd into folder (G4Project_Pacman)
3. git status 
4. git checkout [branch_name]
5. git add .
6. git rm --cached "Pacman AI/Pacman AI.layout"
7. git rm --cached -r "Pacman AI/bin"
8. git rm --cached -r "Pacman AI/obj"
9. git rm --cached "Pacman AI/Pacman AI.depend"
10. git commit -m "Type your message here"
11. git push

How to pull updates?  
1. cd into directory (G4Project_Pacman)
2. git checkout [branch_name]
3. git remote -v (this is to verify origin, if not verified) git remote add upstream [website_link]
4. git fetch upstream (to sync local with upstream)
5. git merge upstream/main (the main can be changed to each branches if you want a older version)

How to start?  
1. cd into directory (Desktop)  
2. git clone the copied website  
3. Do your changes in the folder and save  
4. cd into folder (G4Project_Pacman)
5. git status  
6. git branch -a
(if dont have your branch) git checkout -b Faye
(if have your branch) git checkout Faye
7. git status (check if in the right branch, not main)
8. git add filename
9. git commit -m "Type your message here"
10. git push
