local playerLife = 100



function onTick ()
  if playerLife <= 0 then
   print("PlayerDead")
  end
end
