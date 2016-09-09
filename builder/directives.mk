###################################################
# Make Directives
###################################################

all: bin

bin: $(RBUILD_OBJS) $(ABUILD_OBJS)

	@mkdir -p $(RBUILD_DIR)
	@mkdir -p $(ABUILD_DIR)
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(ANA_DIR)

	@$(ARMAS) $(STARTUP_FILE) $(ASFLAGS) -o $(ABUILD_DIR)/$(notdir $(STARTUP_FILE)).o
	$(ARMLD) $(CFLAGS) $(RBUILD_DIR)/*.o $(ABUILD_DIR)/*.o -o $(BIN_DIR)/$(BIN_NAME).axf $(LDFLAGS)

	@$(ARMOBJCOPY) -O ihex $(BIN_DIR)/$(BIN_NAME).axf $(BIN_DIR)/$(BIN_NAME).hex
	@$(ARMOBJCOPY) -O binary $(BIN_DIR)/$(BIN_NAME).axf $(BIN_DIR)/$(BIN_NAME).bin
	@$(ARMOBJDUMP) -s -t -r -D -x $(BIN_DIR)/$(BIN_NAME).axf > $(ANA_DIR)/objdump
	@$(ARMREADELF) -a $(BIN_DIR)/$(BIN_NAME).axf > $(ANA_DIR)/readelf
	@$(ARMNM) -n $(BIN_DIR)/$(BIN_NAME).axf > $(ANA_DIR)/nm-symbol-list
	@$(ARMSIZE) -A -d -t $(BIN_DIR)/$(BIN_NAME).axf  > $(ANA_DIR)/size
	@$(ARMSIZE) -A $(BIN_DIR)/$(BIN_NAME).axf

	@cp $(BIN_DIR)/$(BIN_NAME).bin $(BIN_DIR)/latest.bin
	@ls -la $(BIN_DIR)/$(BIN_NAME).bin

$(ABUILD_DIR)/%.o: %.c

	@mkdir -p $(ABUILD_DIR)/deps
	@mkdir -p $(LST_DIR)

	@$(ARMCC) -c -MP -MMD -MF $(ABUILD_DIR)/deps/$(@F:.o=.d) \
		$(CFLAGS_I) $(C_APP_FLAGS) $(CFLAGS) \
		-o $@ $<

	@echo $@

-include $(ABUILD_DIR)/deps/*.d

$(RBUILD_DIR)/%.o: %.c

	@mkdir -p $(RBUILD_DIR)/deps
	@mkdir -p $(LST_DIR)

	@$(ARMCC) -c -MP -MMD -MF $(RBUILD_DIR)/deps/$(@F:.o=.d) \
		$(CFLAGS_I) $(CFLAGS) -o $@ $<

	@echo $@

-include $(RBUILD_DIR)/deps/*.d

clean:
	@rm -fr $(CLEAN_DIR)

ocd:
	@$(OPENOCD) -f board/stm32f7discovery.cfg

# Connect to openocd-based gdb server
gdb:
	@$(ARMGDB) $(BIN_DIR)/$(BIN_NAME).axf \
	-ex "target extended-remote localhost:3333" \
	-ex "load" \
	-ex "monitor arm semihosting enable" \
	-ex "monitor tpiu config internal trace.bin uart off 216000000" \
	-ex "monitor itm ports on" \
	-ex "monitor reset init"

# convenience feature if the texane st-util is installed
flash: bin
	$(STFLASH) --reset write $(BIN_DIR)/$(BIN_NAME).bin 0x08000000
