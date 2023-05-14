VULKAN_SDK_DIR = "C:/VulkanSDK/1.3.246.1"

includeDirs = {}
includeDirs["fmt"] = "%{wks.location}/ThirdParty/fmt/include/"
includeDirs["spdlog"] = "%{wks.location}/ThirdParty/spdlog/include/"
includeDirs["glfw"] = "%{wks.location}/ThirdParty/glfw/include/"
includeDirs["glm"] = "%{wks.location}/ThirdParty/glm/include/"

includeDirs["bx"] = "%{wks.location}/ThirdParty/bx/include/"
includeDirs["bimg"] = "%{wks.location}/ThirdParty/bimg/include/"
includeDirs["bgfx"] = "%{wks.location}/ThirdParty/bgfx/include/"

includeDirs["vulkan"] = VULKAN_SDK_DIR.."/Include"

includeDirs["Genesis"] = "%{wks.location}/Genesis/src/"
includeDirs["Runtime"] = "%{wks.location}/Runtime/src/"
