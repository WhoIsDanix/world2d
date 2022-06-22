function world2d.Init()
    x = 10
    y = 10
    speed = 0.1
end
 
function world2d.Update(dt)
    x = x + speed * dt
    y = y + speed * dt
end

function world2d.Render()
    world2d.Graphics.SetDrawColor(255, 255, 255, 255)
    world2d.Graphics.DrawRect(world2d.Graphics.DrawMode.Fill, x, y, 50, 50)
end