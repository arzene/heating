.PHONY: clean All

All:
	@echo "----------Building project:[ HeatController - Debug ]----------"
	@"$(MAKE)" -f  "HeatController.mk"
clean:
	@echo "----------Cleaning project:[ HeatController - Debug ]----------"
	@"$(MAKE)" -f  "HeatController.mk" clean
