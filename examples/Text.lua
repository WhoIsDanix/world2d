function world2d.Init()
    world2d.Window.SetTitle("Text Rendering")
    world2d.Window.SetVSync(true)

    font = world2d.Graphics.Font.new("examples/fonts/AnekMalayalam-Bold.ttf", 48)
    ww, wh = world2d.Window.GetSize()

    text = "FPS: 0"
end

function world2d.Update(dt)
    ww, wh = world2d.Window.GetSize()
    text = "FPS: "..math.floor(1000 / dt)
end

function world2d.Render()
    local tw, th = font:GetTextSize(text)
    world2d.Graphics.Draw(font, text, (ww - tw) / 2, (wh - th) / 2)
end