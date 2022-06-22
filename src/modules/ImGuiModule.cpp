#include "world2d/modules/ImGuiModule.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_sdlrenderer.h"

#include "world2d/lua/structures/ImGuiBool.h"
#include "world2d/lua/structures/ImGuiFloat.h"
#include "world2d/lua/structures/ImGuiInt.h"

#include "world2d/lua/structures/ImGuiFloatArray2.h"
#include "world2d/lua/structures/ImGuiFloatArray3.h"
#include "world2d/lua/structures/ImGuiFloatArray4.h"

#include "world2d/lua/structures/ImGuiIntArray2.h"
#include "world2d/lua/structures/ImGuiIntArray3.h"
#include "world2d/lua/structures/ImGuiIntArray4.h"

#include "world2d/lua/structures/ImGuiStyleColors.h"

#include <vector>

world2d::ImGuiModule::ImGuiModule() : world2d::Module() {

}

world2d::ImGuiModule::~ImGuiModule() {
    if (mImGuiInitialized) {
        ImGui_ImplSDLRenderer_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
    }
}

bool world2d::ImGuiModule::Initialize() {
    // TODO: move this code to InitializeImGuiLuaEnvironment (except InitializeImGui function registration)
    // We need to make so ImGui lua environment is registered only when world2.ImGui.Initialize is called

    sol::state& lua = mEngine->GetLua();

    // Still bad at using sol2
    // Someone teach me please how to use it :c

    sol::table luaWorld2dNamespace { lua.get<sol::table>("world2d") };
    sol::table luaImGuiNamespace { lua.create_table() };

    luaImGuiNamespace["Version"] = IMGUI_VERSION;

    // ===== Structures =====
    luaImGuiNamespace.new_usertype<ImGuiIO>("IO",
        "ConfigFlags", &ImGuiIO::ConfigFlags,
        "BackendFlags", sol::readonly(&ImGuiIO::BackendFlags),
        "DisplaySize", sol::readonly(&ImGuiIO::DisplaySize),
        "DeltaTime", sol::readonly(&ImGuiIO::DeltaTime)
    );

    luaImGuiNamespace.new_usertype<ImGuiStyleColors>("Colors",
        sol::meta_function::index,
        &world2d::ImGuiStyleColors::LuaIndexOperator,

        sol::meta_function::new_index,
        &world2d::ImGuiStyleColors::LuaNewIndexOperator
    );

    luaImGuiNamespace.new_usertype<ImGuiStyle>("Style",
        "Alpha", &ImGuiStyle::Alpha,
        "DisabledAlpha", &ImGuiStyle::DisabledAlpha,
        "WindowPadding", &ImGuiStyle::WindowPadding,
        "WindowRounding", &ImGuiStyle::WindowRounding,
        "WindowBorderSize", &ImGuiStyle::WindowBorderSize,
        "WindowMinSize", &ImGuiStyle::WindowMinSize,
        "WindowTitleAlign", &ImGuiStyle::WindowTitleAlign,
        "WindowMenuButtonPosition", &ImGuiStyle::WindowMenuButtonPosition,
        "ChildRounding", &ImGuiStyle::ChildRounding,
        "ChildBorderSize", &ImGuiStyle::ChildBorderSize,
        "PopupRounding", &ImGuiStyle::PopupRounding,
        "PopupBorderSize", &ImGuiStyle::PopupBorderSize,
        "FramePadding", &ImGuiStyle::FramePadding,
        "FrameRounding", &ImGuiStyle::FrameRounding,
        "FrameBorderSize", &ImGuiStyle::FrameBorderSize,
        "ItemSpacing", &ImGuiStyle::ItemSpacing,
        "ItemInnerSpacing", &ImGuiStyle::ItemInnerSpacing,
        "CellPadding", &ImGuiStyle::CellPadding,
        "TouchExtraPadding", &ImGuiStyle::TouchExtraPadding,
        "IndentSpacing", &ImGuiStyle::IndentSpacing,
        "ColumnsMinSpacing", &ImGuiStyle::ColumnsMinSpacing,
        "ScrollbarSize", &ImGuiStyle::ScrollbarSize,
        "ScrollbarRounding", &ImGuiStyle::ScrollbarRounding,
        "GrabMinSize", &ImGuiStyle::GrabMinSize,
        "GrabRounding", &ImGuiStyle::GrabRounding,
        "LogSliderDeadzone", &ImGuiStyle::LogSliderDeadzone,
        "TabRounding", &ImGuiStyle::TabRounding,
        "TabBorderSize", &ImGuiStyle::TabBorderSize,
        "TabMinWidthForCloseButton", &ImGuiStyle::TabMinWidthForCloseButton,
        "ColorButtonPosition", &ImGuiStyle::ColorButtonPosition,
        "ButtonTextAlign", &ImGuiStyle::ButtonTextAlign,
        "SelectableTextAlign", &ImGuiStyle::SelectableTextAlign,
        "DisplayWindowPadding", &ImGuiStyle::DisplayWindowPadding,
        "DisplaySafeAreaPadding", &ImGuiStyle::DisplaySafeAreaPadding,
        "MouseCursorScale", &ImGuiStyle::MouseCursorScale,
        "AntiAliasedLines", &ImGuiStyle::AntiAliasedLines,
        "AntiAliasedLinesUseTex", &ImGuiStyle::AntiAliasedLinesUseTex,
        "AntiAliasedFill", &ImGuiStyle::AntiAliasedFill,
        "CurveTessellationTol", &ImGuiStyle::CurveTessellationTol,
        "CircleTessellationMaxError", &ImGuiStyle::CircleTessellationMaxError,
        "Colors", sol::property([](ImGuiStyle& self) {
            return world2d::ImGuiStyleColors(self.Colors);
        })
    );

    // TODO: add properties to this usertype
    luaImGuiNamespace.new_usertype<ImFont>("Font");

    luaImGuiNamespace.new_usertype<ImVec2>("Vec2",
        sol::constructors<ImVec2(float, float)>(),

        "x",
        &ImVec2::x,

        "y",
        &ImVec2::y
    );

    luaImGuiNamespace.new_usertype<ImVec4>("Vec4",
        sol::constructors<ImVec4(float, float, float, float)>(),

        "x",
        &ImVec4::x,

        "y",
        &ImVec4::y,

        "z",
        &ImVec4::z,

        "w",
        &ImVec4::w
    );

    luaImGuiNamespace.new_usertype<ImGuiBool>("Bool",
        sol::constructors<ImGuiBool(), ImGuiBool(bool)>(),

        "value",
        &ImGuiBool::value
    );

    luaImGuiNamespace.new_usertype<ImGuiFloat>("Float",
        sol::constructors<ImGuiFloat(), ImGuiFloat(float)>(),

        "value",
        &ImGuiFloat::value
    );

    luaImGuiNamespace.new_usertype<ImGuiInt>("Int",
        sol::constructors<ImGuiInt(), ImGuiInt(int)>(),

        "value",
        &ImGuiInt::value
    );

    luaImGuiNamespace.new_usertype<ImGuiFloatArray2>("FloatArray2",
        sol::constructors<ImGuiFloatArray2(), ImGuiFloatArray2(float, float)>(),

        sol::meta_function::index,
        &ImGuiFloatArray2::LuaIndexOperator,

        sol::meta_function::new_index,
        &ImGuiFloatArray2::LuaNewIndexOperator
    );

    luaImGuiNamespace.new_usertype<ImGuiFloatArray3>("FloatArray3",
        sol::constructors<ImGuiFloatArray3(), ImGuiFloatArray3(float, float, float)>(),

        sol::meta_function::index,
        &ImGuiFloatArray3::LuaIndexOperator,

        sol::meta_function::new_index,
        &ImGuiFloatArray3::LuaNewIndexOperator
    );

    luaImGuiNamespace.new_usertype<ImGuiFloatArray4>("FloatArray4",
        sol::constructors<ImGuiFloatArray4(), ImGuiFloatArray4(float, float, float, float)>(),

        sol::meta_function::index,
        &ImGuiFloatArray4::LuaIndexOperator,

        sol::meta_function::new_index,
        &ImGuiFloatArray4::LuaNewIndexOperator
    );
    // ======================

    // ===== Enums =====
    luaImGuiNamespace.new_enum("Col",
        "Text", ImGuiCol_Text,
        "TextDisabled", ImGuiCol_TextDisabled,
        "WindowBg", ImGuiCol_WindowBg,
        "ChildBg", ImGuiCol_ChildBg,
        "PopupBg", ImGuiCol_PopupBg,
        "Border", ImGuiCol_Border,
        "BorderShadow", ImGuiCol_BorderShadow,
        "FrameBg", ImGuiCol_FrameBg,
        "FrameBgHovered", ImGuiCol_FrameBgHovered,
        "FrameBgActive", ImGuiCol_FrameBgActive,
        "TitleBg", ImGuiCol_TitleBg,
        "TitleBgActive", ImGuiCol_TitleBgActive,
        "TitleBgCollapsed", ImGuiCol_TitleBgCollapsed,
        "MenuBarBg", ImGuiCol_MenuBarBg,
        "ScrollbarBg", ImGuiCol_ScrollbarBg,
        "ScrollbarGrab", ImGuiCol_ScrollbarGrab,
        "ScrollbarGrabHovered", ImGuiCol_ScrollbarGrabHovered,
        "ScrollbarGrabActive", ImGuiCol_ScrollbarGrabActive,
        "CheckMark", ImGuiCol_CheckMark,
        "SliderGrab", ImGuiCol_SliderGrab,
        "SliderGrabActive", ImGuiCol_SliderGrabActive,
        "Button", ImGuiCol_Button,
        "ButtonHovered", ImGuiCol_ButtonHovered,
        "ButtonActive", ImGuiCol_ButtonActive,
        "Header", ImGuiCol_Header,
        "HeaderHovered", ImGuiCol_HeaderHovered,
        "HeaderActive", ImGuiCol_HeaderActive,
        "Separator", ImGuiCol_Separator,
        "SeparatorHovered", ImGuiCol_SeparatorHovered,
        "SeparatorActive", ImGuiCol_SeparatorActive,
        "ResizeGrip", ImGuiCol_ResizeGrip,
        "ResizeGripHovered", ImGuiCol_ResizeGripHovered,
        "ResizeGripActive", ImGuiCol_ResizeGripActive,
        "Tab", ImGuiCol_Tab,
        "TabHovered", ImGuiCol_TabHovered,
        "TabActive", ImGuiCol_TabActive,
        "TabUnfocused", ImGuiCol_TabUnfocused,
        "TabUnfocusedActive", ImGuiCol_TabUnfocusedActive,
        "PlotLines", ImGuiCol_PlotLines,
        "PlotLinesHovered", ImGuiCol_PlotLinesHovered,
        "PlotHistogram", ImGuiCol_PlotHistogram,
        "PlotHistogramHovered", ImGuiCol_PlotHistogramHovered,
        "TableHeaderBg", ImGuiCol_TableHeaderBg,
        "TableBorderStrong", ImGuiCol_TableBorderStrong,
        "TableBorderLight", ImGuiCol_TableBorderLight,
        "TableRowBg", ImGuiCol_TableRowBg,
        "TableRowBgAlt", ImGuiCol_TableRowBgAlt,
        "TextSelectedBg", ImGuiCol_TextSelectedBg,
        "DragDropTarget", ImGuiCol_DragDropTarget,
        "NavHighlight", ImGuiCol_NavHighlight,
        "NavWindowingHighlight", ImGuiCol_NavWindowingHighlight,
        "NavWindowingDimBg", ImGuiCol_NavWindowingDimBg,
        "ModalWindowDimBg", ImGuiCol_ModalWindowDimBg
    );

    luaImGuiNamespace.new_enum("WindowFlags",
        "None", ImGuiWindowFlags_None,
        "NoTitleBar", ImGuiWindowFlags_NoTitleBar,
        "NoResize", ImGuiWindowFlags_NoResize,
        "NoMove", ImGuiWindowFlags_NoMove,
        "NoScrollbar", ImGuiWindowFlags_NoScrollbar,
        "NoScrollWithMouse", ImGuiWindowFlags_NoScrollWithMouse,
        "NoCollapse", ImGuiWindowFlags_NoCollapse,
        "AlwaysAutoResize", ImGuiWindowFlags_AlwaysAutoResize,
        "NoBackground", ImGuiWindowFlags_NoBackground,
        "NoSavedSettings", ImGuiWindowFlags_NoSavedSettings,
        "NoMouseInputs", ImGuiWindowFlags_NoMouseInputs,
        "MenuBar", ImGuiWindowFlags_MenuBar,
        "HorizontalScrollbar", ImGuiWindowFlags_HorizontalScrollbar,
        "NoFocusOnAppearing", ImGuiWindowFlags_NoFocusOnAppearing,
        "NoBringToFrontOnFocus", ImGuiWindowFlags_NoBringToFrontOnFocus,
        "AlwaysUseWindowPadding", ImGuiWindowFlags_AlwaysUseWindowPadding,
        "NoNavInputs", ImGuiWindowFlags_NoNavInputs,
        "NoNavFocus", ImGuiWindowFlags_NoNavFocus,
        "UnsavedDocument", ImGuiWindowFlags_UnsavedDocument
    );

    luaImGuiNamespace.new_enum("InputTextFlags",
        "None", ImGuiInputTextFlags_None,
        "CharsDecimal", ImGuiInputTextFlags_CharsDecimal,
        "CharsHexadecimal", ImGuiInputTextFlags_CharsHexadecimal,
        "CharsUppercase", ImGuiInputTextFlags_CharsUppercase,
        "CharsNoBlank", ImGuiInputTextFlags_CharsNoBlank,
        "AutoSelectAll", ImGuiInputTextFlags_AutoSelectAll,
        "EnterReturnsTrue", ImGuiInputTextFlags_EnterReturnsTrue,
        "CallbackCompletion", ImGuiInputTextFlags_CallbackCompletion,
        "CallbackHistory", ImGuiInputTextFlags_CallbackHistory,
        "CallbackAlways", ImGuiInputTextFlags_CallbackAlways,
        "CallbackCharFilter", ImGuiInputTextFlags_CallbackCharFilter,
        "AllowTabInput", ImGuiInputTextFlags_AllowTabInput,
        "CtrlEnterForNewLine", ImGuiInputTextFlags_CtrlEnterForNewLine,
        "NoHorizontalScroll", ImGuiInputTextFlags_NoHorizontalScroll,
        "AlwaysInsertMode", ImGuiInputTextFlags_AlwaysInsertMode,
        "ReadOnly", ImGuiInputTextFlags_ReadOnly,
        "Password", ImGuiInputTextFlags_Password,
        "NoUndoRedo", ImGuiInputTextFlags_NoUndoRedo,
        "CharsScientific", ImGuiInputTextFlags_CharsScientific,
        "CallbackResize", ImGuiInputTextFlags_CallbackResize
    );

    luaImGuiNamespace.new_enum("TreeNodeFlags",
        "None", ImGuiTreeNodeFlags_None,
        "Selected", ImGuiTreeNodeFlags_Selected,
        "Framed", ImGuiTreeNodeFlags_Framed,
        "AllowItemOverlap", ImGuiTreeNodeFlags_AllowItemOverlap,
        "NoTreePushOnOpen", ImGuiTreeNodeFlags_NoTreePushOnOpen,
        "NoAutoOpenOnLog", ImGuiTreeNodeFlags_NoAutoOpenOnLog,
        "DefaultOpen", ImGuiTreeNodeFlags_DefaultOpen,
        "OpenOnDoubleClick", ImGuiTreeNodeFlags_OpenOnDoubleClick,
        "OpenOnArrow", ImGuiTreeNodeFlags_OpenOnArrow,
        "Leaf", ImGuiTreeNodeFlags_Leaf,
        "Bullet", ImGuiTreeNodeFlags_Bullet,
        "FramePadding", ImGuiTreeNodeFlags_FramePadding,
        "SpanAvailWidth", ImGuiTreeNodeFlags_SpanAvailWidth,
        "SpanFullWidth", ImGuiTreeNodeFlags_SpanFullWidth
    );

    luaImGuiNamespace.new_enum("SelectableFlags",
        "None", ImGuiSelectableFlags_None,
        "DontClosePopups", ImGuiSelectableFlags_DontClosePopups,
        "SpanAllColumns", ImGuiSelectableFlags_SpanAllColumns,
        "AllowDoubleClick", ImGuiSelectableFlags_AllowDoubleClick,
        "Disabled", ImGuiSelectableFlags_Disabled
    );

    luaImGuiNamespace.new_enum("ComboFlags",
        "None", ImGuiComboFlags_None,
        "PopupAlignLeft", ImGuiComboFlags_PopupAlignLeft,
        "HeightSmall", ImGuiComboFlags_HeightSmall,
        "HeightRegular", ImGuiComboFlags_HeightRegular,
        "HeightLarge", ImGuiComboFlags_HeightLarge,
        "HeightLargest", ImGuiComboFlags_HeightLargest,
        "NoArrowButton", ImGuiComboFlags_NoArrowButton,
        "NoPreview", ImGuiComboFlags_NoPreview
    );

    luaImGuiNamespace.new_enum("TabBarFlags",
        "None", ImGuiTabBarFlags_None,
        "Reorderable", ImGuiTabBarFlags_Reorderable,
        "AutoSelectNewTabs", ImGuiTabBarFlags_AutoSelectNewTabs,
        "TabListPopupButton", ImGuiTabBarFlags_TabListPopupButton,
        "NoCloseWithMiddleMouseButton", ImGuiTabBarFlags_NoCloseWithMiddleMouseButton,
        "NoTabListScrollingButtons", ImGuiTabBarFlags_NoTabListScrollingButtons,
        "NoTooltip", ImGuiTabBarFlags_NoTooltip,
        "FittingPolicyResizeDown", ImGuiTabBarFlags_FittingPolicyResizeDown,
        "FittingPolicyScroll", ImGuiTabBarFlags_FittingPolicyScroll
    );

    luaImGuiNamespace.new_enum("TabItemFlags",
        "None", ImGuiTabItemFlags_None,
        "UnsavedDocument", ImGuiTabItemFlags_UnsavedDocument,
        "SetSelected", ImGuiTabItemFlags_SetSelected,
        "NoCloseWithMiddleMouseButton", ImGuiTabItemFlags_NoCloseWithMiddleMouseButton
    );

    luaImGuiNamespace.new_enum("FocusedFlags",
        "None", ImGuiFocusedFlags_None,
        "ChildWindows", ImGuiFocusedFlags_ChildWindows,
        "RootWindow", ImGuiFocusedFlags_RootWindow,
        "AnyWindow", ImGuiFocusedFlags_AnyWindow
    );

    luaImGuiNamespace.new_enum("HoveredFlags",
        "None", ImGuiHoveredFlags_None,
        "ChildWindows", ImGuiHoveredFlags_ChildWindows,
        "RootWindow", ImGuiHoveredFlags_RootWindow,
        "AnyWindow", ImGuiHoveredFlags_AnyWindow,
        "AllowWhenBlockedByPopup", ImGuiHoveredFlags_AllowWhenBlockedByPopup,
        "AllowWhenBlockedByActiveItem", ImGuiHoveredFlags_AllowWhenBlockedByActiveItem,
        "AllowWhenOverlapped", ImGuiHoveredFlags_AllowWhenOverlapped,
        "AllowWhenDisabled", ImGuiHoveredFlags_AllowWhenDisabled,
        "RectOnly", ImGuiHoveredFlags_RectOnly // ???
    );

    luaImGuiNamespace.new_enum("DragDropFlags",
        "None", ImGuiDragDropFlags_None,
        "SourceNoPreviewTooltip", ImGuiDragDropFlags_SourceNoPreviewTooltip,
        "SourceNoDisableHover", ImGuiDragDropFlags_SourceNoDisableHover,
        "SourceNoHoldToOpenOthers", ImGuiDragDropFlags_SourceNoHoldToOpenOthers,
        "SourceAllowNullID", ImGuiDragDropFlags_SourceAllowNullID,
        "SourceExtern", ImGuiDragDropFlags_SourceExtern,
        "SourceAutoExpirePayload", ImGuiDragDropFlags_SourceAutoExpirePayload,
        "AcceptBeforeDelivery", ImGuiDragDropFlags_AcceptBeforeDelivery,
        "AcceptNoDrawDefaultRect", ImGuiDragDropFlags_AcceptNoDrawDefaultRect,
        "AcceptNoPreviewTooltip", ImGuiDragDropFlags_AcceptNoPreviewTooltip
    );

    luaImGuiNamespace.new_enum("Dir",
        "None", ImGuiDir_None,
        "Left", ImGuiDir_Left,
        "Right", ImGuiDir_Right,
        "Up", ImGuiDir_Up,
        "Down", ImGuiDir_Down
    );

    luaImGuiNamespace.new_enum("ColorEdit",
        "None", ImGuiColorEditFlags_None,
        "NoAlpha", ImGuiColorEditFlags_NoAlpha,
        "NoPicker", ImGuiColorEditFlags_NoPicker,
        "NoOptions", ImGuiColorEditFlags_NoOptions,
        "NoSmallPreview", ImGuiColorEditFlags_NoSmallPreview,
        "NoInputs", ImGuiColorEditFlags_NoInputs,
        "NoTooltip", ImGuiColorEditFlags_NoTooltip,
        "NoLabel", ImGuiColorEditFlags_NoLabel,
        "NoSidePreview", ImGuiColorEditFlags_NoSidePreview,
        "NoDragDrop", ImGuiColorEditFlags_NoDragDrop,
        "NoBorder", ImGuiColorEditFlags_NoBorder,
        "AlphaBar", ImGuiColorEditFlags_AlphaBar,
        "AlphaPreview", ImGuiColorEditFlags_AlphaPreview,
        "HDR", ImGuiColorEditFlags_HDR, // Marked as WIP in documentation
        "DisplayRGB", ImGuiColorEditFlags_DisplayRGB,
        "DisplayHSV", ImGuiColorEditFlags_DisplayHSV,
        "DisplayHex", ImGuiColorEditFlags_DisplayHex,
        "Uint8", ImGuiColorEditFlags_Uint8,
        "Float", ImGuiColorEditFlags_Float,
        "PickerHueBar", ImGuiColorEditFlags_PickerHueBar,
        "PickerHueWheel", ImGuiColorEditFlags_PickerHueWheel,
        "InputRGB", ImGuiColorEditFlags_InputRGB,
        "InputHSV", ImGuiColorEditFlags_InputHSV
    );

    luaImGuiNamespace.new_enum("Cond",
        "Always", ImGuiCond_Always,
        "Once", ImGuiCond_Once,
        "FirstUseEver", ImGuiCond_FirstUseEver
    );

    luaImGuiNamespace.new_enum("Dir",
        "None", ImGuiDir_None,
        "Left", ImGuiDir_Left,
        "Right", ImGuiDir_Right,
        "Up", ImGuiDir_Up,
        "Down", ImGuiDir_Down
    );
    // =================

    // ===== ImGui Initialization =====
    luaImGuiNamespace.set_function("Initialize", [&]() {
        this->InitializeImGui();
    });
    // ================================

    // ===== Multiple Flags =====
    // (if you need multiple flags, you should use bitwise OR operator, but Lua have it in bit32 library but I struggle to load it)

    luaImGuiNamespace.set_function("MultipleFlags", [&](sol::variadic_args flags) {
        int newflags = 0;

        for (auto flag : flags) {
            if (flag.get_type() == sol::type::number) {
                newflags |= flag.as<int>();
            } else {
                // TODO: throw an error
                luaL_error(lua.lua_state(), "Invalid number");
            }
        }

        return newflags;
    });

    // ==========================

    // ===== Main =====
    luaImGuiNamespace.set_function("GetIO", &ImGui::GetIO);
    luaImGuiNamespace.set_function("GetStyle", &ImGui::GetStyle);

    luaImGuiNamespace.set_function("Button", sol::overload(
        [&](const char* label) {
            return ImGui::Button(label);
        },

        [&](const char* label, const ImVec2& size) {
            return ImGui::Button(label, size);
        }
    ));

    luaImGuiNamespace.set_function("SmallButton", [&](const char* label) {
        return ImGui::SmallButton(label);
    });

    luaImGuiNamespace.set_function("InvisibleButton", [&](const char* strId, const ImVec2& size) {
        return ImGui::InvisibleButton(strId, size);
    });

    luaImGuiNamespace.set_function("Checkbox", [&](const char* label, ImGuiBool* imGuiBool) {
        return ImGui::Checkbox(label, &(imGuiBool->value));
    });

    luaImGuiNamespace.set_function("RadioButton", [&](const char* label, bool active) {
        return ImGui::RadioButton(label, active);
    });

    // TODO: add this version of function: bool RadioButton(const char* label, int* v, int v_button)

    luaImGuiNamespace.set_function("ProgressBar", sol::overload(
        [&](float fraction) {
            ImGui::ProgressBar(fraction);
        },

        [&](float fraction, const ImVec2& sizeArg) {
            ImGui::ProgressBar(fraction, sizeArg);
        },

        [&](float fraction, const ImVec2& sizeArg, const char* overlay) {
            ImGui::ProgressBar(fraction, sizeArg, overlay);
        }
    ));

    luaImGuiNamespace.set_function("Bullet", [&]() {
        ImGui::Bullet();
    });
    // ================

    // ===== Demo =====
    luaImGuiNamespace.set_function("ShowDemoWindow", sol::overload(
        [&]() {
            ImGui::ShowDemoWindow();
        },

        [&](ImGuiBool* pOpen) {
            ImGui::ShowDemoWindow(&(pOpen->value));
        }
    ));

    luaImGuiNamespace.set_function("ShowAboutWindow", sol::overload(
        [&]() {
            ImGui::ShowAboutWindow();
        },

        [&](ImGuiBool* pOpen) {
            ImGui::ShowAboutWindow(&(pOpen->value));
        }
    ));

    luaImGuiNamespace.set_function("ShowMetricsWindow", [&](ImGuiBool* pOpen) {
        ImGui::ShowMetricsWindow(&(pOpen->value));
    });

    luaImGuiNamespace.set_function("ShowStyleSelector", &ImGui::ShowStyleSelector);
    luaImGuiNamespace.set_function("ShowFontSelector", &ImGui::ShowFontSelector);
    luaImGuiNamespace.set_function("ShowUserGuide", &ImGui::ShowUserGuide);
    // ================

    // ===== Styles =====
    luaImGuiNamespace.set_function("StyleColorsDark", &ImGui::StyleColorsDark);
    luaImGuiNamespace.set_function("StyleColorsClassic", &ImGui::StyleColorsClassic);
    luaImGuiNamespace.set_function("StyleColorsLight", &ImGui::StyleColorsLight);
    // ========================

    // ===== Windows =====
    luaImGuiNamespace.set_function("Begin", sol::overload(
        [&](const char* name) {
            return ImGui::Begin(name);
        },

        [&](const char* name, ImGuiBool* pOpen) {
            return ImGui::Begin(name, &(pOpen->value));
        },

        [&](const char* name, ImGuiBool* pOpen, ImGuiWindowFlags flags) {
            return ImGui::Begin(name, &(pOpen->value), flags);
        }
    ));

    luaImGuiNamespace.set_function("End", &ImGui::End);
    // ===================

    // ===== Child Windows =====
    luaImGuiNamespace.set_function("BeginChild", sol::overload(
        [&](const char* strId) {
            return ImGui::BeginChild(strId);
        },

        [&](const char* strId, const ImVec2& size) {
            return ImGui::BeginChild(strId, size);
        },

        [&](const char* strId, const ImVec2& size, bool border) {
            return ImGui::BeginChild(strId, size, border);
        },

        [&](const char* strId, const ImVec2& size, bool border, ImGuiWindowFlags flags) {
            return ImGui::BeginChild(strId, size, border, flags);
        }
    ));

    // BeginChild version with ImGuiID
    // bool BeginChild(ImGuiID id, const ImVec2& size = ImVec2(0,0), bool border = false, ImGuiWindowFlags flags = 0)

    luaImGuiNamespace.set_function("EndChild", &ImGui::EndChild);
    // =========================

    // ===== Window Utilities =====
    luaImGuiNamespace.set_function("IsWindowAppearing", &ImGui::IsWindowAppearing);
    luaImGuiNamespace.set_function("IsWindowCollapsed", &ImGui::IsWindowCollapsed);

    luaImGuiNamespace.set_function("IsWindowFocused", sol::overload(
        [&]() {
            return ImGui::IsWindowFocused();
        },

        [&](ImGuiFocusedFlags flags) {
            return ImGui::IsWindowFocused(flags);
        }
    ));

    luaImGuiNamespace.set_function("IsWindowHovered", sol::overload(
        [&]() {
            return ImGui::IsWindowHovered();
        },

        [&](ImGuiHoveredFlags flags) {
            return ImGui::IsWindowHovered(flags);
        }
    ));

    // ImDrawList* GetWindowDrawList()

    luaImGuiNamespace.set_function("GetWindowPos", &ImGui::GetWindowPos);
    luaImGuiNamespace.set_function("GetWindowSize", &ImGui::GetWindowSize);
    luaImGuiNamespace.set_function("GetWindowWidth", &ImGui::GetWindowWidth);
    luaImGuiNamespace.set_function("GetWindowHeight", &ImGui::GetWindowHeight);
    // ============================

    // ===== Next Window Utilities =====
    luaImGuiNamespace.set_function("SetNextWindowPos", sol::overload(
        [&](const ImVec2& pos) {
            ImGui::SetNextWindowPos(pos);
        },

        [&](const ImVec2& pos, ImGuiCond cond) {
            ImGui::SetNextWindowPos(pos, cond);
        },

        [&](const ImVec2& pos, ImGuiCond cond, const ImVec2& pivot) {
            ImGui::SetNextWindowPos(pos, cond, pivot);
        }
    ));

    luaImGuiNamespace.set_function("SetNextWindowSize", sol::overload(
        [&](const ImVec2& size) {
            ImGui::SetNextWindowSize(size);
        },

        [&](const ImVec2& size, ImGuiCond cond) {
            ImGui::SetNextWindowSize(size, cond);
        }
    ));
    // =================================

    // ===== Windows Scrolling =====
    luaImGuiNamespace.set_function("GetScrollX", &ImGui::GetScrollX);
    luaImGuiNamespace.set_function("GetScrollY", &ImGui::GetScrollY);
    luaImGuiNamespace.set_function("GetScrollMaxX", &ImGui::GetScrollMaxX);
    luaImGuiNamespace.set_function("GetScrollMaxY", &ImGui::GetScrollMaxY);
    luaImGuiNamespace.set_function("SetScrollX", &ImGui::SetScrollX);
    luaImGuiNamespace.set_function("SetScrollY", &ImGui::SetScrollY);

    luaImGuiNamespace.set_function("SetScrollHereX", sol::overload(
        [&]() {
            ImGui::SetScrollHereX();
        },

        [&](float centerXRatio) {
            ImGui::SetScrollHereX(centerXRatio);
        }
    ));

    luaImGuiNamespace.set_function("SetScrollHereY", sol::overload(
        [&]() {
            ImGui::SetScrollHereY();
        },

        [&](float centerYRatio) {
            ImGui::SetScrollHereY(centerYRatio);
        }
    ));

    luaImGuiNamespace.set_function("SetScrollFromPosX", sol::overload(
        [&](float localX) {
            ImGui::SetScrollFromPosX(localX);
        },

        [&](float localX, float centerXRatio) {
            ImGui::SetScrollFromPosX(localX, centerXRatio);
        }
    ));

    luaImGuiNamespace.set_function("SetScrollFromPosY", sol::overload(
        [&](float localY) {
            ImGui::SetScrollFromPosY(localY);
        },

        [&](float localY, float centerYRatio) {
            ImGui::SetScrollFromPosY(localY, centerYRatio);
        }
    ));
    // =============================

    // ===== Parameters stacks (shared) =====
    luaImGuiNamespace.set_function("PushFont", &ImGui::PushFont);
    luaImGuiNamespace.set_function("PopFont", &ImGui::PopFont);

    luaImGuiNamespace.set_function("PushStyleColor", sol::overload(
        [&](ImGuiCol idx, ImU32 col) {
            ImGui::PushStyleColor(idx, col);
        },

        [&](ImGuiCol idx, const ImVec4& col) {
            ImGui::PushStyleColor(idx, col);
        }
    ));

    luaImGuiNamespace.set_function("PopStyleColor", sol::overload(
        [&]() {
            ImGui::PopStyleColor();
        },

        [&](int count) {
            ImGui::PopStyleColor(count);
        }
    ));

    luaImGuiNamespace.set_function("PushStyleVar", sol::overload(
        [&](ImGuiStyleVar idx, float val) {
            ImGui::PushStyleVar(idx, val);
        },

        [&](ImGuiStyleVar idx, const ImVec2& val) {
            ImGui::PushStyleVar(idx, val);
        }
    ));

    luaImGuiNamespace.set_function("PopStyleVar", sol::overload(
        [&]() {
            ImGui::PopStyleVar();
        },

        [&](int count) {
            ImGui::PopStyleVar(count);
        }
    ));

    // TODO: ImFont* GetFont()

    luaImGuiNamespace.set_function("GetFontSize", &ImGui::GetFontSize);
    luaImGuiNamespace.set_function("GetFontTexUvWhitePixel", &ImGui::GetFontTexUvWhitePixel);
    
    luaImGuiNamespace.set_function("GetColorU32", sol::overload(
        [&](ImGuiCol idx) {
            return ImGui::GetColorU32(idx);
        },

        [&](ImGuiCol idx, float alphaMul) {
            return ImGui::GetColorU32(idx, alphaMul);
        },

        [&](const ImVec4& col) {
            return ImGui::GetColorU32(col);
        },

        [&](ImU32 col) {
            return ImGui::GetColorU32(col);
        }
    ));
    // ======================================

    // ===== Parameters stacks (current window) =====
    luaImGuiNamespace.set_function("PushItemWidth", &ImGui::PushItemWidth);
    luaImGuiNamespace.set_function("PopItemWidth", &ImGui::PopItemWidth);
    luaImGuiNamespace.set_function("SetNextItemWidth", &ImGui::SetNextItemWidth);
    luaImGuiNamespace.set_function("CalcItemWidth", &ImGui::CalcItemWidth);

    luaImGuiNamespace.set_function("PushTextWrapPos", sol::overload(
        [&]() {
            ImGui::PushTextWrapPos();
        },

        [&](float wrapLocalPosX) {
            ImGui::PushTextWrapPos(wrapLocalPosX);
        }
    ));

    luaImGuiNamespace.set_function("PopTextWrapPos", &ImGui::PopTextWrapPos);
    luaImGuiNamespace.set_function("PushAllowKeyboardFocus", &ImGui::PushAllowKeyboardFocus);
    luaImGuiNamespace.set_function("PopAllowKeyboardFocus", &ImGui::PopAllowKeyboardFocus);
    luaImGuiNamespace.set_function("PushButtonRepeat", &ImGui::PushButtonRepeat);
    luaImGuiNamespace.set_function("PopButtonRepeat", &ImGui::PopButtonRepeat);
    // ==============================================

    // ===== Cursor / Layout =====
    luaImGuiNamespace.set_function("Separator", &ImGui::Separator);
    luaImGuiNamespace.set_function("NewLine", &ImGui::SameLine);
    luaImGuiNamespace.set_function("Spacing", &ImGui::Spacing);
    luaImGuiNamespace.set_function("Dummy", &ImGui::Dummy);

    luaImGuiNamespace.set_function("Indent", sol::overload(
        [&]() {
            ImGui::Indent();
        },

        [&](float indentW) {
            ImGui::Indent(indentW);
        }
    ));

    luaImGuiNamespace.set_function("Unindent", sol::overload(
        [&]() {
            ImGui::Unindent();
        },

        [&](float indentW) {
            ImGui::Unindent(indentW);
        }
    ));

    luaImGuiNamespace.set_function("BeginGroup", &ImGui::BeginGroup);
    luaImGuiNamespace.set_function("EndGroup", &ImGui::EndGroup);
    luaImGuiNamespace.set_function("GetCursorPos", &ImGui::GetCursorPos);
    luaImGuiNamespace.set_function("GetCursorPosX", &ImGui::GetCursorPosX);
    luaImGuiNamespace.set_function("GetCursorPosY", &ImGui::GetCursorPosY);
    luaImGuiNamespace.set_function("SetCursorPos", &ImGui::SetCursorPos);
    luaImGuiNamespace.set_function("SetCursorPosX", &ImGui::SetCursorPosX);
    luaImGuiNamespace.set_function("SetCursorPosY", &ImGui::SetCursorPosY);
    luaImGuiNamespace.set_function("GetCursorStartPos", &ImGui::GetCursorStartPos);
    luaImGuiNamespace.set_function("GetCursorScreenPos", &ImGui::GetCursorScreenPos);
    luaImGuiNamespace.set_function("SetCursorScreenPos", &ImGui::SetCursorScreenPos);
    luaImGuiNamespace.set_function("AlignTextToFramePadding", &ImGui::AlignTextToFramePadding);
    luaImGuiNamespace.set_function("GetTextLineHeight", &ImGui::GetTextLineHeight);
    luaImGuiNamespace.set_function("GetTextLineHeightWithSpacing", &ImGui::GetTextLineHeightWithSpacing);
    luaImGuiNamespace.set_function("GetFrameHeight", &ImGui::GetFrameHeight);
    luaImGuiNamespace.set_function("GetFrameHeightWithSpacing", &ImGui::GetFrameHeightWithSpacing);
    // ===========================

    // ===== Text =====
    luaImGuiNamespace.set_function("Text", [&](const char* text) {
        ImGui::Text(text);
    });

    luaImGuiNamespace.set_function("TextColored", [&](const ImVec4& col, const char* text) {
        ImGui::TextColored(col, text);
    });

    luaImGuiNamespace.set_function("TextDisabled", [&](const char* text) {
        ImGui::TextDisabled(text);
    });

    luaImGuiNamespace.set_function("TextWrapped", [&](const char* text) {
        ImGui::TextWrapped(text);
    });

    luaImGuiNamespace.set_function("LabelText", [&](const char* label, const char* text) {
        ImGui::LabelText(label, text);
    });

    luaImGuiNamespace.set_function("BulletText", [&](const char* text) {
        ImGui::BulletText(text);
    });
    // ================

    // ===== Combo Box =====
    luaImGuiNamespace.set_function("BeginCombo", sol::overload(
        [&](const char* label, const char* previewValue) {
            return ImGui::BeginCombo(label, previewValue);
        },

        [&](const char* label, const char* previewValue, ImGuiComboFlags flags) {
            return ImGui::BeginCombo(label, previewValue, flags);
        }
    ));

    luaImGuiNamespace.set_function("EndCombo", [&]() {
        ImGui::EndCombo();
    });

    luaImGuiNamespace.set_function("DragFloat", sol::overload(
        [&](const char* label, ImGuiFloat* v) {
            return ImGui::DragFloat(label, &(v->value));
        },

        [&](const char* label, ImGuiFloat* v, float vSpeed) {
            return ImGui::DragFloat(label, &(v->value), vSpeed);
        },

        [&](const char* label, ImGuiFloat* v, float vSpeed, float vMin) {
            return ImGui::DragFloat(label, &(v->value), vSpeed, vMin);
        },

        [&](const char* label, ImGuiFloat* v, float vSpeed, float vMin, float vMax) {
            return ImGui::DragFloat(label, &(v->value), vSpeed, vMin, vMax);
        },

        [&](const char* label, ImGuiFloat* v, float vSpeed, float vMin, float vMax, const char* format) {
            return ImGui::DragFloat(label, &(v->value), vSpeed, vMin, vMax, format);
        },

        [&](const char* label, ImGuiFloat* v, float vSpeed, float vMin, float vMax, const char* format, float power) {
            return ImGui::DragFloat(label, &(v->value), vSpeed, vMin, vMax, format, power);
        }
    ));

    luaImGuiNamespace.set_function("DragFloat2", sol::overload(
        [&](const char* label, ImGuiFloatArray2* v) {
            return ImGui::DragFloat2(label, v->data());
        },

        [&](const char* label, ImGuiFloatArray2* v, float vSpeed) {
            return ImGui::DragFloat2(label, v->data(), vSpeed);
        },

        [&](const char* label, ImGuiFloatArray2* v, float vSpeed, float vMin) {
            return ImGui::DragFloat2(label, v->data(), vSpeed, vMin);
        },

        [&](const char* label, ImGuiFloatArray2* v, float vSpeed, float vMin, float vMax) {
            return ImGui::DragFloat2(label, v->data(), vSpeed, vMin, vMax);
        },

        [&](const char* label, ImGuiFloatArray2* v, float vSpeed, float vMin, float vMax, const char* format) {
            return ImGui::DragFloat2(label, v->data(), vSpeed, vMin, vMax, format);
        },

        [&](const char* label, ImGuiFloatArray2* v, float vSpeed, float vMin, float vMax, const char* format, float power) {
            return ImGui::DragFloat2(label, v->data(), vSpeed, vMin, vMax, format, power);
        }
    ));

    luaImGuiNamespace.set_function("DragFloat3", sol::overload(
        [&](const char* label, ImGuiFloatArray3* v) {
            return ImGui::DragFloat3(label, v->data());
        },

        [&](const char* label, ImGuiFloatArray3* v, float vSpeed) {
            return ImGui::DragFloat3(label, v->data(), vSpeed);
        },

        [&](const char* label, ImGuiFloatArray3* v, float vSpeed, float vMin) {
            return ImGui::DragFloat3(label, v->data(), vSpeed, vMin);
        },

        [&](const char* label, ImGuiFloatArray3* v, float vSpeed, float vMin, float vMax) {
            return ImGui::DragFloat3(label, v->data(), vSpeed, vMin, vMax);
        },

        [&](const char* label, ImGuiFloatArray3* v, float vSpeed, float vMin, float vMax, const char* format) {
            return ImGui::DragFloat3(label, v->data(), vSpeed, vMin, vMax, format);
        },

        [&](const char* label, ImGuiFloatArray3* v, float vSpeed, float vMin, float vMax, const char* format, float power) {
            return ImGui::DragFloat3(label, v->data(), vSpeed, vMin, vMax, format, power);
        }
    ));

    luaImGuiNamespace.set_function("DragFloat4", sol::overload(
        [&](const char* label, ImGuiFloatArray4* v) {
            return ImGui::DragFloat4(label, v->data());
        },

        [&](const char* label, ImGuiFloatArray4* v, float vSpeed) {
            return ImGui::DragFloat4(label, v->data(), vSpeed);
        },

        [&](const char* label, ImGuiFloatArray4* v, float vSpeed, float vMin) {
            return ImGui::DragFloat4(label, v->data(), vSpeed, vMin);
        },

        [&](const char* label, ImGuiFloatArray4* v, float vSpeed, float vMin, float vMax) {
            return ImGui::DragFloat4(label, v->data(), vSpeed, vMin, vMax);
        },

        [&](const char* label, ImGuiFloatArray4* v, float vSpeed, float vMin, float vMax, const char* format) {
            return ImGui::DragFloat4(label, v->data(), vSpeed, vMin, vMax, format);
        },

        [&](const char* label, ImGuiFloatArray4* v, float vSpeed, float vMin, float vMax, const char* format, float power) {
            return ImGui::DragFloat4(label, v->data(), vSpeed, vMin, vMax, format, power);
        }
    ));

    luaImGuiNamespace.set_function("DragFloatRange2", sol::overload(
        [&](const char* label, ImGuiFloat* vCurrentMin, ImGuiFloat* vCurrentMax) {
            return ImGui::DragFloatRange2(label, &(vCurrentMin->value), &(vCurrentMax->value));
        },

        [&](const char* label, ImGuiFloat* vCurrentMin, ImGuiFloat* vCurrentMax, float vSpeed) {
            return ImGui::DragFloatRange2(label, &(vCurrentMin->value), &(vCurrentMax->value), vSpeed);
        },

        [&](const char* label, ImGuiFloat* vCurrentMin, ImGuiFloat* vCurrentMax, float vSpeed, float vMin) {
            return ImGui::DragFloatRange2(label, &(vCurrentMin->value), &(vCurrentMax->value), vSpeed, vMin);
        },

        [&](const char* label, ImGuiFloat* vCurrentMin, ImGuiFloat* vCurrentMax, float vSpeed, float vMin, float vMax) {
            return ImGui::DragFloatRange2(label, &(vCurrentMin->value), &(vCurrentMax->value), vSpeed, vMin, vMax);
        },

        [&](const char* label, ImGuiFloat* vCurrentMin, ImGuiFloat* vCurrentMax, float vSpeed, float vMin, float vMax, const char* format) {
            return ImGui::DragFloatRange2(label, &(vCurrentMin->value), &(vCurrentMax->value), vSpeed, vMin, vMax, format);
        },

        [&](const char* label, ImGuiFloat* vCurrentMin, ImGuiFloat* vCurrentMax, float vSpeed, float vMin, float vMax, const char* format, const char* formatMax) {
            return ImGui::DragFloatRange2(label, &(vCurrentMin->value), &(vCurrentMax->value), vSpeed, vMin, vMax, format, formatMax);
        },

        [&](const char* label, ImGuiFloat* vCurrentMin, ImGuiFloat* vCurrentMax, float vSpeed, float vMin, float vMax, const char* format, const char* formatMax, float power) {
            return ImGui::DragFloatRange2(label, &(vCurrentMin->value), &(vCurrentMax->value), vSpeed, vMin, vMax, format, formatMax, power);
        }
    ));

    luaImGuiNamespace.set_function("DragInt", sol::overload(
        [&](const char* label, ImGuiInt* v) {
            return ImGui::DragInt(label, &(v->value));
        },

        [&](const char* label, ImGuiInt* v, float vSpeed) {
            return ImGui::DragInt(label, &(v->value), vSpeed);
        },

        [&](const char* label, ImGuiInt* v, float vSpeed, int vMin) {
            return ImGui::DragInt(label, &(v->value), vSpeed, vMin);
        },

        [&](const char* label, ImGuiInt* v, float vSpeed, int vMin, int vMax) {
            return ImGui::DragInt(label, &(v->value), vSpeed, vMin, vMax);
        },

        [&](const char* label, ImGuiInt* v, float vSpeed, int vMin, int vMax, const char* format) {
            return ImGui::DragInt(label, &(v->value), vSpeed, vMin, vMax, format);
        }

        // TODO: add DragInt2, DragInt3, DragInt4, DragIntRange2, DragScalar, DragScalarN
    ));
    // =====================

    // ===== Sliders =====
    luaImGuiNamespace.set_function("SliderFloat", sol::overload(
        [&](const char* label, ImGuiFloat* v, float vMin, float vMax) {
            return ImGui::SliderFloat(label, &(v->value), vMin, vMax);
        },

        [&](const char* label, ImGuiFloat* v, float vMin, float vMax, const char* format) {
            return ImGui::SliderFloat(label, &(v->value), vMin, vMax, format);
        },

        [&](const char* label, ImGuiFloat* v, float vMin, float vMax, const char* format, float power) {
            return ImGui::SliderFloat(label, &(v->value), vMin, vMax, format, power);
        }
    ));

    luaImGuiNamespace.set_function("SliderFloat2", sol::overload(
        [&](const char* label, ImGuiFloatArray2* v, float vMin, float vMax) {
            return ImGui::SliderFloat2(label, v->data(), vMin, vMax);
        },

        [&](const char* label, ImGuiFloatArray2* v, float vMin, float vMax, const char* format) {
            return ImGui::SliderFloat2(label, v->data(), vMin, vMax, format);
        },

        [&](const char* label, ImGuiFloatArray2* v, float vMin, float vMax, const char* format, float power) {
            return ImGui::SliderFloat2(label, v->data(), vMin, vMax, format, power);
        }
    ));

    luaImGuiNamespace.set_function("SliderFloat3", sol::overload(
        [&](const char* label, ImGuiFloatArray3* v, float vMin, float vMax) {
            return ImGui::SliderFloat3(label, v->data(), vMin, vMax);
        },

        [&](const char* label, ImGuiFloatArray3* v, float vMin, float vMax, const char* format) {
            return ImGui::SliderFloat3(label, v->data(), vMin, vMax, format);
        },

        [&](const char* label, ImGuiFloatArray3* v, float vMin, float vMax, const char* format, float power) {
            return ImGui::SliderFloat3(label, v->data(), vMin, vMax, format, power);
        }
    ));

    luaImGuiNamespace.set_function("SliderFloat4", sol::overload(
        [&](const char* label, ImGuiFloatArray4* v, float vMin, float vMax) {
            return ImGui::SliderFloat4(label, v->data(), vMin, vMax);
        },

        [&](const char* label, ImGuiFloatArray4* v, float vMin, float vMax, const char* format) {
            return ImGui::SliderFloat4(label, v->data(), vMin, vMax, format);
        },

        [&](const char* label, ImGuiFloatArray4* v, float vMin, float vMax, const char* format, float power) {
            return ImGui::SliderFloat4(label, v->data(), vMin, vMax, format, power);
        }
    ));

    luaImGuiNamespace.set_function("SliderAngle", sol::overload(
        [&](const char* label, ImGuiFloat* vRad) {
            return ImGui::SliderAngle(label, &(vRad->value));
        },

        [&](const char* label, ImGuiFloat* vRad, float vDegreesMin) {
            return ImGui::SliderAngle(label, &(vRad->value), vDegreesMin);
        },

        [&](const char* label, ImGuiFloat* vRad, float vDegreesMin, float vDegreesMax) {
            return ImGui::SliderAngle(label, &(vRad->value), vDegreesMin, vDegreesMax);
        },

        [&](const char* label, ImGuiFloat* vRad, float vDegreesMin, float vDegreesMax, const char* format) {
            return ImGui::SliderAngle(label, &(vRad->value), vDegreesMin, vDegreesMax, format);
        }
    ));

    luaImGuiNamespace.set_function("SliderInt", sol::overload(
        [&](const char* label, ImGuiInt* v, int vMin, int vMax) {
            return ImGui::SliderInt(label, &(v->value), vMin, vMax);
        },

        [&](const char* label, ImGuiInt* v, int vMin, int vMax, const char* format) {
            return ImGui::SliderInt(label, &(v->value), vMin, vMax, format);
        }
    ));

    luaImGuiNamespace.set_function("SliderInt2", sol::overload(
        [&](const char* label, ImGuiIntArray2* v, int vMin, int vMax) {
            return ImGui::SliderInt2(label, v->data(), vMin, vMax);
        },

        [&](const char* label, ImGuiIntArray2* v, int vMin, int vMax, const char* format) {
            return ImGui::SliderInt2(label, v->data(), vMin, vMax, format);
        }
    ));

    luaImGuiNamespace.set_function("SliderInt3", sol::overload(
        [&](const char* label, ImGuiIntArray3* v, int vMin, int vMax) {
            return ImGui::SliderInt3(label, v->data(), vMin, vMax);
        },

        [&](const char* label, ImGuiIntArray3* v, int vMin, int vMax, const char* format) {
            return ImGui::SliderInt3(label, v->data(), vMin, vMax, format);
        }
    ));

    luaImGuiNamespace.set_function("SliderInt4", sol::overload(
        [&](const char* label, ImGuiIntArray4* v, int vMin, int vMax) {
            return ImGui::SliderInt4(label, v->data(), vMin, vMax);
        },

        [&](const char* label, ImGuiIntArray4* v, int vMin, int vMax, const char* format) {
            return ImGui::SliderInt4(label, v->data(), vMin, vMax, format);
        }
    ));
    // ===================

    // ===== Input with Keyboard =====
    luaImGuiNamespace.set_function("InputFloat", sol::overload(
        [&](const char* label, ImGuiFloat* v) {
            return ImGui::InputFloat(label, &(v->value));
        },

        [&](const char* label, ImGuiFloat* v, float step) {
            return ImGui::InputFloat(label, &(v->value), step);
        },

        [&](const char* label, ImGuiFloat* v, float step, float step_fast) {
            return ImGui::InputFloat(label, &(v->value), step, step_fast);
        },

        [&](const char* label, ImGuiFloat* v, float step, float step_fast, const char* format) {
            return ImGui::InputFloat(label, &(v->value), step, step_fast, format);
        },

        [&](const char* label, ImGuiFloat* v, float step, float step_fast, const char* format, ImGuiInputTextFlags flags) {
            return ImGui::InputFloat(label, &(v->value), step, step_fast, format, flags);
        }
    ));

    luaImGuiNamespace.set_function("InputFloat2", sol::overload(
        [&](const char* label, ImGuiFloatArray2* v) {
            return ImGui::InputFloat2(label, v->data());
        },

        [&](const char* label, ImGuiFloatArray2* v, const char* format) {
            return ImGui::InputFloat2(label, v->data(), format);
        },

        [&](const char* label, ImGuiFloatArray2* v, const char* format, ImGuiInputTextFlags flags) {
            return ImGui::InputFloat2(label, v->data(), format, flags);
        }
    ));

    luaImGuiNamespace.set_function("InputFloat3", sol::overload(
        [&](const char* label, ImGuiFloatArray3* v) {
            return ImGui::InputFloat3(label, v->data());
        },

        [&](const char* label, ImGuiFloatArray3* v, const char* format) {
            return ImGui::InputFloat3(label, v->data(), format);
        },

        [&](const char* label, ImGuiFloatArray3* v, const char* format, ImGuiInputTextFlags flags) {
            return ImGui::InputFloat3(label, v->data(), format, flags);
        }
    ));

    luaImGuiNamespace.set_function("InputFloat4", sol::overload(
        [&](const char* label, ImGuiFloatArray4* v) {
            return ImGui::InputFloat4(label, v->data());
        },

        [&](const char* label, ImGuiFloatArray4* v, const char* format) {
            return ImGui::InputFloat4(label, v->data(), format);
        },

        [&](const char* label, ImGuiFloatArray4* v, const char* format, ImGuiInputTextFlags flags) {
            return ImGui::InputFloat4(label, v->data(), format, flags);
        }
    ));

    luaImGuiNamespace.set_function("InputInt", sol::overload(
        [&](const char* label, ImGuiInt* v) {
            return ImGui::InputInt(label, &(v->value));
        },

        [&](const char* label, ImGuiInt* v, int step) {
            return ImGui::InputInt(label, &(v->value), step);
        },

        [&](const char* label, ImGuiInt* v, int step, int step_fast) {
            return ImGui::InputInt(label, &(v->value), step, step_fast);
        },

        [&](const char* label, ImGuiInt* v, int step, int step_fast, ImGuiInputTextFlags flags) {
            return ImGui::InputInt(label, &(v->value), step, step_fast, flags);
        }
    ));

    luaImGuiNamespace.set_function("InputInt2", sol::overload(
        [&](const char* label, ImGuiIntArray2* v) {
            return ImGui::InputInt2(label, v->data());
        },

        [&](const char* label, ImGuiIntArray2* v, ImGuiInputTextFlags flags) {
            return ImGui::InputInt2(label, v->data(), flags);
        }
    ));

    luaImGuiNamespace.set_function("InputInt3", sol::overload(
        [&](const char* label, ImGuiIntArray3* v) {
            return ImGui::InputInt3(label, v->data());
        },

        [&](const char* label, ImGuiIntArray3* v, ImGuiInputTextFlags flags) {
            return ImGui::InputInt3(label, v->data(), flags);
        }
    ));

    luaImGuiNamespace.set_function("InputInt4", sol::overload(
        [&](const char* label, ImGuiIntArray4* v) {
            return ImGui::InputInt4(label, v->data());
        },

        [&](const char* label, ImGuiIntArray4* v, ImGuiInputTextFlags flags) {
            return ImGui::InputInt4(label, v->data(), flags);
        }
    ));
    // ===============================

    // ===== Color Editor/Picker =====
    luaImGuiNamespace.set_function("ColorEdit3", sol::overload(
        [&](const char* label, ImGuiFloatArray3* col) {
            return ImGui::ColorEdit3(label, col->data());
        },

        [&](const char* label, ImGuiFloatArray3* col, ImGuiColorEditFlags flags) {
            return ImGui::ColorEdit3(label, col->data(), flags);
        }
    ));

    luaImGuiNamespace.set_function("ColorEdit4", sol::overload(
        [&](const char* label, ImGuiFloatArray4* col) {
            return ImGui::ColorEdit4(label, col->data());
        },

        [&](const char* label, ImGuiFloatArray4* col, ImGuiColorEditFlags flags) {
            return ImGui::ColorEdit4(label, col->data(), flags);
        }
    ));

    luaImGuiNamespace.set_function("ColorPicker3", sol::overload(
        [&](const char* label, ImGuiFloatArray3* col) {
            return ImGui::ColorPicker3(label, col->data());
        },

        [&](const char* label, ImGuiFloatArray3* col, ImGuiColorEditFlags flags) {
            return ImGui::ColorPicker3(label, col->data(), flags);
        }
    ));

    luaImGuiNamespace.set_function("ColorPicker4", sol::overload(
        [&](const char* label, ImGuiFloatArray4* col) {
            return ImGui::ColorPicker4(label, col->data());
        },

        [&](const char* label, ImGuiFloatArray4* col, ImGuiColorEditFlags flags) {
            return ImGui::ColorPicker4(label, col->data(), flags);
        },

        [&](const char* label, ImGuiFloatArray4* col, ImGuiColorEditFlags flags, const ImGuiFloat* ref_col) {
            return ImGui::ColorPicker4(label, col->data(), flags, &(ref_col->value));
        }
    ));

    luaImGuiNamespace.set_function("ColorButton", sol::overload(
        [&](const char* descId, const ImVec4& col) {
            return ImGui::ColorButton(descId, col);
        },

        [&](const char* descId, const ImVec4& col, ImGuiColorEditFlags flags) {
            return ImGui::ColorButton(descId, col, flags);
        },

        [&](const char* descId, const ImVec4& col, ImGuiColorEditFlags flags, ImVec2 size) {
            return ImGui::ColorButton(descId, col, flags, size);
        }
    ));

    luaImGuiNamespace.set_function("SetColorEditOptions", [&](ImGuiColorEditFlags flags) {
        ImGui::SetColorEditOptions(flags);
    });
    // ===============================

    // ===== Selectables =====
    luaImGuiNamespace.set_function("Selectable", sol::overload(
        [&](const char* label) {
            return ImGui::Selectable(label);
        },

        [&](const char* label, bool selected) {
            return ImGui::Selectable(label, selected);
        },

        [&](const char* label, bool selected, ImGuiSelectableFlags flags) {
            return ImGui::Selectable(label, selected, flags);
        },

        [&](const char* label, bool selected, ImGuiSelectableFlags flags, const ImVec2& size) {
            return ImGui::Selectable(label, selected, flags, size);
        },

        [&](const char* label, ImGuiBool* pSelected) {
            return ImGui::Selectable(label, &(pSelected->value));
        },

        [&](const char* label, ImGuiBool* pSelected, ImGuiSelectableFlags flags) {
            return ImGui::Selectable(label, &(pSelected->value), flags);
        },

        [&](const char* label, ImGuiBool* pSelected, ImGuiSelectableFlags flags, const ImVec2& size) {
            return ImGui::Selectable(label, &(pSelected->value), flags, size);
        }
    ));
    // =======================

    // ===== Data Plotting =====
    luaImGuiNamespace.set_function("PlotLines", [&](const char* label, sol::table values) {
        std::vector<float> newvalues;
        newvalues.reserve(values.size());

        for (auto pair : values) {
            if (pair.first.get_type() != sol::type::number) continue;

            if (pair.second.get_type() == sol::type::number) {
                newvalues.push_back(pair.second.as<float>());
            } else {
                luaL_error(lua.lua_state(), "Invalid value for PlotLines");
            }
        }

        ImGui::PlotLines(label, newvalues.data(), newvalues.size());
    });
    // =========================

    // ===== Menus =====
    luaImGuiNamespace.set_function("BeginMenuBar", &ImGui::BeginMenuBar);
    luaImGuiNamespace.set_function("EndMenuBar", &ImGui::EndMenuBar);
    luaImGuiNamespace.set_function("BeginMainMenuBar", &ImGui::BeginMainMenuBar);
    luaImGuiNamespace.set_function("EndMainMenuBar", &ImGui::EndMainMenuBar);

    luaImGuiNamespace.set_function("BeginMenu", sol::overload(
        [&](const char* label) {
            return ImGui::BeginMenu(label);
        },

        [&](const char* label, bool enabled) {
            return ImGui::BeginMenu(label, enabled);
        }
    ));

    luaImGuiNamespace.set_function("EndMenu", &ImGui::EndMenu);

    luaImGuiNamespace.set_function("MenuItem", sol::overload(
        [&](const char* label) {
            return ImGui::MenuItem(label);
        },

        [&](const char* label, const char* shortcut) {
            return ImGui::MenuItem(label, shortcut);
        },

        [&](const char* label, const char* shortcut, bool selected) {
            return ImGui::MenuItem(label, shortcut, selected);
        },

        [&](const char* label, const char* shortcut, bool selected, bool enabled) {
            return ImGui::MenuItem(label, shortcut, selected, enabled);
        }

        // TODO: bool MenuItem(const char* label, const char* shortcut, bool* p_selected, bool enabled = true)
    ));
    // =================

    // ===== Tooltips =====
    luaImGuiNamespace.set_function("BeginTooltip", [&]() {
        ImGui::BeginTooltip();
    });

    luaImGuiNamespace.set_function("EndTooltip", [&]() {
        ImGui::EndTooltip();
    });

    luaImGuiNamespace.set_function("SetTooltip", [&](const char* text) {
        return ImGui::SetTooltip(text);
    });
    // ====================

    // ===== Tab Bars, Tabs =====
    luaImGuiNamespace.set_function("BeginTabBar", sol::overload(
        [&](const char* strId) {
            return ImGui::BeginTabBar(strId);
        },

        [&](const char* strId, ImGuiTabBarFlags flags) {
            return ImGui::BeginTabBar(strId, flags);
        }
    ));

    luaImGuiNamespace.set_function("EndTabBar", &ImGui::EndTabBar);

    luaImGuiNamespace.set_function("BeginTabItem", sol::overload(
        [&](const char* label) {
            return ImGui::BeginTabItem(label);
        },

        [&](const char* label, ImGuiBool* pOpen) {
            return ImGui::BeginTabItem(label, &(pOpen->value));
        },

        [&](const char* label, ImGuiBool* pOpen, ImGuiTabItemFlags flags) {
            return ImGui::BeginTabItem(label, &(pOpen->value), flags);
        }
    ));

    luaImGuiNamespace.set_function("EndTabItem", &ImGui::EndTabItem);
    luaImGuiNamespace.set_function("SetTabItemClosed", &ImGui::SetTabItemClosed);
    // ==========================

    luaWorld2dNamespace["ImGui"] = luaImGuiNamespace;
    return true;
}

void world2d::ImGuiModule::OnEvent(SDL_Event& event) {
    if (mImGuiInitialized) {
        ImGui_ImplSDL2_ProcessEvent(&event);
    }
}

void world2d::ImGuiModule::Update(double deltaTime) {
    if (mImGuiInitialized) {
        ImGui_ImplSDLRenderer_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
    }
}

void world2d::ImGuiModule::Render() {
    if (mImGuiInitialized) {
        ImGui::Render();
        ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
    }
}

void world2d::ImGuiModule::InitializeImGui() {
    if (mImGuiInitialized) {
        return;
    }

    IMGUI_CHECKVERSION();

    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    SDL_Window* window = mEngine->GetSDLWindow();
    SDL_Renderer* renderer = mEngine->GetSDLRenderer();

    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer_Init(renderer);

    mImGuiInitialized = true;
}

world2d::ImGuiModule* world2d::ImGuiModule::Get() {
    static ImGuiModule currentModule;
    return &currentModule;
}