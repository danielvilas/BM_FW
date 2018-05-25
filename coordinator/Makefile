.PHONY: clean All

All:
	@echo "----------Building project:[ rp_datalogger - Debug ]----------"
	@cd "rp_datalogger_dummy" && "$(MAKE)" -f  "Makefile"
	@echo "----------Building project:[ bmCoordinator - Debug ]----------"
	@cd "bmCoordinator" && "$(MAKE)" -f  "Makefile"
clean:
	@echo "----------Cleaning project:[ rp_datalogger - Debug ]----------"
	@cd "rp_datalogger_dummy" && "$(MAKE)" -f  "Makefile"  clean
	@echo "----------Cleaning project:[ bmCoordinator - Debug ]----------"
	@cd "bmCoordinator_dummy" && "$(MAKE)" -f  "Makefile" clean
