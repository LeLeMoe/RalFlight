# ----------------------------------------------------------------------------------------------------
# Copyright © 2016 - 2018 LeLe570929726. All rights reserved.
# 
# @Project: RalFlight
# @License: Licensed under GNU General Public License v3.
# @Description: A free and open-source flight simulator.
#
# @Create: 2018/3/25 by LeLe570929726
# ----------------------------------------------------------------------------------------------------

# 3rdParties
include("3rdParty/Boost/Boost.cmake")
include("3rdParty/Vulkan/Vulkan.cmake")
include("3rdParty/OpenAL/OpenAL.cmake")

# Windows only
if(${RF_OS} STREQUAL "RF_OS_WIN")
  include("3rdParty/DirectX/DirectX.cmake")
endif()