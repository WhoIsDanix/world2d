#include "world2d/modules/ImGuiModule.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_sdlrenderer.h"

#include "world2d/lua/imgui/structures/Bool.h"
#include "world2d/lua/imgui/structures/Float.h"
#include "world2d/lua/imgui/structures/Int.h"

#include "world2d/lua/imgui/structures/FloatArray2.h"
#include "world2d/lua/imgui/structures/FloatArray3.h"
#include "world2d/lua/imgui/structures/FloatArray4.h"

#include "world2d/lua/imgui/structures/IntArray2.h"
#include "world2d/lua/imgui/structures/IntArray3.h"
#include "world2d/lua/imgui/structures/IntArray4.h"

#include "world2d/lua/imgui/structures/String.h"
#include "world2d/lua/imgui/structures/StyleColors.h"

#include "world2d/lua/imgui/Widget.h"

#include "world2d/lua/imgui/widgets/ChildWindowWidget.h"
#include "world2d/lua/imgui/widgets/ClippingWidget.h"
#include "world2d/lua/imgui/widgets/ColorEditorPickerWidget.h"
#include "world2d/lua/imgui/widgets/ColorUtilitiesWidget.h"
#include "world2d/lua/imgui/widgets/ComboBoxWidget.h"
#include "world2d/lua/imgui/widgets/CursorLayoutWidget.h"
#include "world2d/lua/imgui/widgets/DataPlottingWidget.h"
#include "world2d/lua/imgui/widgets/DemoWidget.h"
#include "world2d/lua/imgui/widgets/FocusActivationWidget.h"
#include "world2d/lua/imgui/widgets/ItemWidgetUtilitiesWidget.h"
#include "world2d/lua/imgui/widgets/KeyboardInputWidget.h"
#include "world2d/lua/imgui/widgets/ListBoxWidget.h"
#include "world2d/lua/imgui/widgets/MainWidget.h"
#include "world2d/lua/imgui/widgets/MenuWidget.h"
#include "world2d/lua/imgui/widgets/MiscellaneousUtilitiesWidget.h"
#include "world2d/lua/imgui/widgets/NextWindowUtilitiesWidget.h"
#include "world2d/lua/imgui/widgets/ParametersStacksCurrentWindowWidget.h"
#include "world2d/lua/imgui/widgets/ParametersStacksSharedWidget.h"
#include "world2d/lua/imgui/widgets/SelectableWidget.h"
#include "world2d/lua/imgui/widgets/SliderWidget.h"
#include "world2d/lua/imgui/widgets/StyleWidget.h"
#include "world2d/lua/imgui/widgets/TabWidget.h"
#include "world2d/lua/imgui/widgets/TextUtilitiesWidget.h"
#include "world2d/lua/imgui/widgets/TextWidget.h"
#include "world2d/lua/imgui/widgets/TooltipWidget.h"
#include "world2d/lua/imgui/widgets/WindowScrollingWidget.h"
#include "world2d/lua/imgui/widgets/WindowUtilitiesWidget.h"
#include "world2d/lua/imgui/widgets/WindowWidget.h"

#include <vector>
#include <tuple>

world2d::ImGuiModule::ImGuiModule() : world2d::Module() {

}

world2d::ImGuiModule::~ImGuiModule() {
    if (mImGuiInitialized) {
        ImGui_ImplSDLRenderer_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ::ImGui::DestroyContext();
    }
}

bool world2d::ImGuiModule::Initialize() {
    sol::state& lua = mEngine->GetLua();

    sol::table luaWorld2dNamespace { lua.get<sol::table>("world2d") };
    sol::table luaImGuiNamespace { lua.create_table() };

    luaImGuiNamespace["Version"] = IMGUI_VERSION;

    // ===== Structures =====

    // TODO: Finish ImGuiIO
    luaImGuiNamespace.new_usertype<ImGuiIO>("IO",
        "ConfigFlags", &ImGuiIO::ConfigFlags,
        "BackendFlags", sol::readonly(&ImGuiIO::BackendFlags),
        "DisplaySize", sol::readonly(&ImGuiIO::DisplaySize),
        "DeltaTime", sol::readonly(&ImGuiIO::DeltaTime),
        "IniSavingRate", &ImGuiIO::IniSavingRate,
        "IniFilename", &ImGuiIO::IniFilename,
        "LogFilename", &ImGuiIO::LogFilename,
        "MouseDoubleClickTime", &ImGuiIO::MouseDoubleClickTime,
        "MouseDoubleClickMaxDist", &ImGuiIO::MouseDoubleClickMaxDist,
        "MouseDragThreshold", &ImGuiIO::MouseDragThreshold,
        "KeyRepeatDelay", &ImGuiIO::KeyRepeatDelay,
        "KeyRepeatRate", &ImGuiIO::KeyRepeatRate,
        // void* UserData

        "Fonts", &ImGuiIO::Fonts,
        "FontGlobalScale", &ImGuiIO::FontGlobalScale,
        "FontAllowUserScaling", &ImGuiIO::FontAllowUserScaling,
        "FontDefault", &ImGuiIO::FontDefault,
        "DisplayFramebufferScale", &ImGuiIO::DisplayFramebufferScale,

        "MouseDrawCursor", &ImGuiIO::MouseDrawCursor,
        "ConfigMacOSXBehaviors", &ImGuiIO::ConfigMacOSXBehaviors,
        "ConfigInputTrickleEventQueue", &ImGuiIO::ConfigInputTrickleEventQueue,
        "ConfigInputTextCursorBlink", &ImGuiIO::ConfigInputTextCursorBlink,
        "ConfigDragClickToInputText", &ImGuiIO::ConfigDragClickToInputText,
        "ConfigWindowsResizeFromEdges", &ImGuiIO::ConfigWindowsResizeFromEdges,
        "ConfigWindowsMoveFromTitleBarOnly", &ImGuiIO::ConfigWindowsMoveFromTitleBarOnly,
        "ConfigMemoryCompactTimer", &ImGuiIO::ConfigMemoryCompactTimer,

        "BackendPlatformName", sol::readonly(&ImGuiIO::BackendPlatformName),
        "BackendRendererName", sol::readonly(&ImGuiIO::BackendRendererName),

        "WantCaptureMouse", sol::readonly(&ImGuiIO::WantCaptureMouse),
        "WantCaptureKeyboard", sol::readonly(&ImGuiIO::WantCaptureKeyboard),
        "WantTextInput", sol::readonly(&ImGuiIO::WantTextInput),
        "WantSetMousePos", sol::readonly(&ImGuiIO::WantSetMousePos),
        "WantSaveIniSettings", sol::readonly(&ImGuiIO::WantSaveIniSettings),
        "NavActive", sol::readonly(&ImGuiIO::NavActive),
        "NavVisible", sol::readonly(&ImGuiIO::NavVisible),
        "Framerate", sol::readonly(&ImGuiIO::Framerate),
        "MetricsRenderVertices", sol::readonly(&ImGuiIO::MetricsRenderVertices),
        "MetricsRenderIndices", sol::readonly(&ImGuiIO::MetricsRenderIndices),
        "MetricsRenderWindows", sol::readonly(&ImGuiIO::MetricsRenderWindows),
        "MetricsActiveWindows", sol::readonly(&ImGuiIO::MetricsActiveWindows),
        "MetricsActiveAllocations", sol::readonly(&ImGuiIO::MetricsActiveAllocations),
        "MouseDelta", sol::readonly(&ImGuiIO::MouseDelta),

        "MousePos", sol::readonly(&ImGuiIO::MousePos),
        // bool MouseDown[5];
        "MouseWheel", sol::readonly(&ImGuiIO::MouseWheel),
        "MouseWheelH", sol::readonly(&ImGuiIO::MouseWheelH),
        "KeyCtrl", sol::readonly(&ImGuiIO::KeyCtrl),
        "KeyShift", sol::readonly(&ImGuiIO::KeyShift),
        "KeyAlt", sol::readonly(&ImGuiIO::KeyAlt),
        "KeySuper", sol::readonly(&ImGuiIO::KeySuper)
        // float NavInputs[ImGuiNavInput_COUNT];
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
            return world2d::ImGui::StyleColors(self.Colors);
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

    luaImGuiNamespace.new_usertype<::world2d::ImGui::Bool>("Bool",
        sol::constructors<::world2d::ImGui::Bool(), ::world2d::ImGui::Bool(bool)>(),

        "value",
        &::world2d::ImGui::Bool::value
    );

    luaImGuiNamespace.new_usertype<::world2d::ImGui::Float>("Float",
        sol::constructors<::world2d::ImGui::Float(), ::world2d::ImGui::Float(float)>(),

        "value",
        &::world2d::ImGui::Float::value
    );

    luaImGuiNamespace.new_usertype<::world2d::ImGui::FloatArray2>("FloatArray2",
        sol::constructors<::world2d::ImGui::FloatArray2(), ::world2d::ImGui::FloatArray2(float, float)>(),

        sol::meta_function::index,
        &::world2d::ImGui::FloatArray2::LuaIndexOperator,

        sol::meta_function::new_index,
        &::world2d::ImGui::FloatArray2::LuaNewIndexOperator
    );

    luaImGuiNamespace.new_usertype<::world2d::ImGui::FloatArray3>("FloatArray3",
        sol::constructors<::world2d::ImGui::FloatArray3(), ::world2d::ImGui::FloatArray3(float, float, float)>(),

        sol::meta_function::index,
        &::world2d::ImGui::FloatArray3::LuaIndexOperator,

        sol::meta_function::new_index,
        &::world2d::ImGui::FloatArray3::LuaNewIndexOperator
    );

    luaImGuiNamespace.new_usertype<::world2d::ImGui::FloatArray4>("FloatArray4",
        sol::constructors<::world2d::ImGui::FloatArray4(), ::world2d::ImGui::FloatArray4(float, float, float, float)>(),

        sol::meta_function::index,
        &::world2d::ImGui::FloatArray4::LuaIndexOperator,

        sol::meta_function::new_index,
        &::world2d::ImGui::FloatArray4::LuaNewIndexOperator
    );

    luaImGuiNamespace.new_usertype<::world2d::ImGui::Int>("Int",
        sol::constructors<::world2d::ImGui::Int(), ::world2d::ImGui::Int(int)>(),

        "value",
        &::world2d::ImGui::Int::value
    );

    luaImGuiNamespace.new_usertype<::world2d::ImGui::IntArray2>("IntArray2",
        sol::constructors<::world2d::ImGui::IntArray2(), ::world2d::ImGui::IntArray2(float, float)>(),

        sol::meta_function::index,
        &::world2d::ImGui::IntArray2::LuaIndexOperator,

        sol::meta_function::new_index,
        &::world2d::ImGui::IntArray2::LuaNewIndexOperator
    );

    luaImGuiNamespace.new_usertype<::world2d::ImGui::IntArray3>("IntArray3",
        sol::constructors<::world2d::ImGui::IntArray3(), ::world2d::ImGui::IntArray3(float, float, float)>(),

        sol::meta_function::index,
        &::world2d::ImGui::IntArray3::LuaIndexOperator,

        sol::meta_function::new_index,
        &::world2d::ImGui::IntArray3::LuaNewIndexOperator
    );

    luaImGuiNamespace.new_usertype<::world2d::ImGui::IntArray4>("IntArray4",
        sol::constructors<::world2d::ImGui::IntArray4(), ::world2d::ImGui::IntArray4(float, float, float, float)>(),

        sol::meta_function::index,
        &::world2d::ImGui::IntArray4::LuaIndexOperator,

        sol::meta_function::new_index,
        &::world2d::ImGui::IntArray4::LuaNewIndexOperator
    );

    luaImGuiNamespace.new_usertype<::world2d::ImGui::String>("String",
        sol::constructors<::world2d::ImGui::String(), ::world2d::ImGui::String(std::string)>(),
        "value", &::world2d::ImGui::String::value
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

    // ===== Widget Initialization =====
    std::vector<world2d::ImGui::Widget*> widgets {
        world2d::ImGui::ChildWindowWidget::Get(),
        world2d::ImGui::ClippingWidget::Get(),
        world2d::ImGui::ColorEditorPickerWidget::Get(),
        world2d::ImGui::ColorUtilitiesWidget::Get(),
        world2d::ImGui::ComboBoxWidget::Get(),
        world2d::ImGui::CursorLayoutWidget::Get(),
        world2d::ImGui::DataPlottingWidget::Get(),
        world2d::ImGui::DemoWidget::Get(),
        world2d::ImGui::FocusActivationWidget::Get(),
        world2d::ImGui::ItemWidgetUtilitiesWidget::Get(),
        world2d::ImGui::KeyboardInputWidget::Get(),
        world2d::ImGui::ListBoxWidget::Get(),
        world2d::ImGui::MainWidget::Get(),
        world2d::ImGui::MenuWidget::Get(),
        world2d::ImGui::MiscellaneousUtilitiesWidget::Get(),
        world2d::ImGui::NextWindowUtilitiesWidget::Get(),
        world2d::ImGui::ParametersStacksCurrentWindowWidget::Get(),
        world2d::ImGui::ParametersStacksSharedWidget::Get(),
        world2d::ImGui::SelectableWidget::Get(),
        world2d::ImGui::SliderWidget::Get(),
        world2d::ImGui::StyleWidget::Get(),
        world2d::ImGui::TabWidget::Get(),
        world2d::ImGui::TextUtilitiesWidget::Get(),
        world2d::ImGui::TextWidget::Get(),
        world2d::ImGui::TooltipWidget::Get(),
        world2d::ImGui::WindowScrollingWidget::Get(),
        world2d::ImGui::WindowUtilitiesWidget::Get(),
        world2d::ImGui::WindowWidget::Get()
    };

    for (world2d::ImGui::Widget* widget : widgets) {
        widget->SetLuaEnvironment(luaImGuiNamespace);
    }
    // =================================

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
        ::ImGui::NewFrame();
    }
}

void world2d::ImGuiModule::Render() {
    if (mImGuiInitialized) {
        ::ImGui::Render();
        ImGui_ImplSDLRenderer_RenderDrawData(::ImGui::GetDrawData());
    }
}

void world2d::ImGuiModule::InitializeImGui() {
    if (mImGuiInitialized) {
        return;
    }

    ::ImGui::DebugCheckVersionAndDataLayout(IMGUI_VERSION, sizeof(ImGuiIO), sizeof(ImGuiStyle), sizeof(ImVec2), sizeof(ImVec4), sizeof(ImDrawVert), sizeof(ImDrawIdx));

    ::ImGui::CreateContext();
    ::ImGui::StyleColorsDark();

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