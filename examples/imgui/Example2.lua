function world2d.Init()
    ImGui = world2d.ImGui
    ImGui.Initialize()

    str = ImGui.String.new()

    fontidx = 1
    fontselectables = {
        "AnekMalayalam Bold",
        "AnekMalayalam Extra Bold",
        "AnekMalayalam Extra Light",
        "AnekMalayalam Light",
        "AnekMalayalam Medium",
        "AnekMalayalam Regular",
        "AnekMalayalam Semi Bold",
        "AnekMalayalam Thin"
    }

    fontsize = 28
    fonts = {
        world2d.Graphics.Font.new("examples/fonts/AnekMalayalam-Bold.ttf", fontsize),
        world2d.Graphics.Font.new("examples/fonts/AnekMalayalam-ExtraBold.ttf", fontsize),
        world2d.Graphics.Font.new("examples/fonts/AnekMalayalam-ExtraLight.ttf", fontsize),
        world2d.Graphics.Font.new("examples/fonts/AnekMalayalam-Light.ttf", fontsize),
        world2d.Graphics.Font.new("examples/fonts/AnekMalayalam-Medium.ttf", fontsize),
        world2d.Graphics.Font.new("examples/fonts/AnekMalayalam-Regular.ttf", fontsize),
        world2d.Graphics.Font.new("examples/fonts/AnekMalayalam-SemiBold.ttf", fontsize),
        world2d.Graphics.Font.new("examples/fonts/AnekMalayalam-Thin.ttf", fontsize),
    }
end

function world2d.Render()
    world2d.Graphics.SetDrawColor(128, 128, 128, 255)
    world2d.Graphics.Clear()

    ImGui.Begin("Window")

    if ImGui.BeginListBox("Fonts") then
        for i = 1, #fontselectables do
            local selected = (i == fontidx)

            if ImGui.Selectable(fontselectables[i], selected) then
                fontidx = i
            end
        end

        ImGui.EndListBox()
    end

    ImGui.Separator()

    ImGui.Text("Text will be rendered on the screen")
    ImGui.InputTextMultiline("Text Input", str)

    ImGui.End()

    world2d.Graphics.Draw(fonts[fontidx], str.value, 50, 50)
end