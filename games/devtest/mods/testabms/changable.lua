local abm_first_run = false;

minetest.register_chatcommand("changableABM", {
	params = "enable | disable | interval_1 | interval_5",
	description = "Active/Deactivate changable ABM.",
	func = function(name, param)
		if param == "enable" then
			minetest.change_abm("testchangableabm:abm", {
					interval = 30.0,
				})
			abm_first_run = true;
			return true, "ABM has been enabled."
		elseif param == "interval_1" then
			minetest.change_abm("testchangableabm:abm", {
					interval = 1.0,
				})
			abm_first_run = true;
				return true, "ABM has been enabled with interval 1."
		elseif param == "interval_5" then
			minetest.change_abm("testchangableabm:abm", {
					interval = 5.0,
				})
			abm_first_run = true;
				return true, "ABM has been enabled with interval 5."
		elseif param == "disable" then
			minetest.change_abm("testchangableabm:abm", {
					interval = -30.0,
				})
			return true, "ABM has been disabled."
		else
			return false, "Check /help changableABB for allowed parameters."
		end
	end,
})

minetest.register_abm({
	name = "testchangableabm:abm",
	nodenames = "basenodes:stone",
	interval = -30.0,
	chance = 1,
	cancelable = false,
	action = function(pos)
		if abm_first_run then
			minetest.chat_send_all("Changable ABM runs first time after enable.")
			abm_first_run = false
		end
	end,
})
