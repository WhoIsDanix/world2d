-- This was made as a joke c:

function world2d.Init()
    world2d.Window.SetTitle("butter dogs (it's just collision check)")
    world2d.Window.SetResizable(false)

    player = world2d.Graphics.Sprite.new("examples/dog.png", 20, 20, 80, 80)
    player_speed = 1

    butterdog = world2d.Graphics.Sprite.new("examples/dog.png", 120, 120, 80, 80)

    print("Movement: WASD")
end

function world2d.Update(dt)
    local x_inc = 0
    local y_inc = 0

    if world2d.Keyboard.IsKeyPressed("W") then
        y_inc = y_inc - player_speed * dt
    end

    if world2d.Keyboard.IsKeyPressed("S") then
        y_inc = y_inc + player_speed * dt
    end

    if world2d.Keyboard.IsKeyPressed("D") then
        x_inc = x_inc + player_speed * dt
    end

    if world2d.Keyboard.IsKeyPressed("A") then
        x_inc = x_inc - player_speed * dt
    end

    player.x = player.x + x_inc
    player.y = player.y + y_inc

    if player:IsCollidingWith(butterdog) then
        player.x = player.x - x_inc
        player.y = player.y - y_inc
    end
end

function world2d.Render()
    world2d.Graphics.Draw(player)
    world2d.Graphics.Draw(butterdog)
end