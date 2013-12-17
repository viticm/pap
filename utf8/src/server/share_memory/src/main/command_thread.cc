#include "server/share_memory/main/command_thread.h"
#include "server/common/base/log.h"

CommandThread::CommandThread() {
  __ENTER_FUNCTION
    active_ = true;
  __LEAVE_FUNCTION
}

CommandThread::~CommandThread() {
  //do nothing
}

void CommandThread::run() {
  __ENTER_FUNCTION
    while (is_active()) {
      bool result = false;
      result = CommandParser::handleinput();
      Assert(result);
    }
  __LEAVE_FUNCTION
}


bool CommandParser::handleinput() {
  __ENTER_FUNCTION
    bool result = true;
    char cmd[kCmdSize];
    memset(cmd, '\0', sizeof(cmd));
    int32_t charcount = 0;
    int32_t charinput;
    while (true) {
      charinput = getchar();
      if ('\n' == charinput) break;
      if (charcount > sizeof(cmd) - 1) break;
      cmd[charcount] = charinput;
      ++charcount;
    }
    command_state_t state = parser_commandtype(cmd);
    switch (state.type) {
      case kCmdSaveAll: {
        g_command_thread.command_config.state = state;
        g_log->fast_save_log(kShareMemoryLogFile, "start save all%s", LF);
      }
      case kCmdClearAll: {
        g_command_thread.command_config.state = state;
        g_log->fast_save_log(kShareMemoryLogFile, "start clear all%s", LF); 
      }
      default: {
        g_log->fast_save_log(kShareMemoryLogFile, "unkown command%s", LF);
      }
    }
    return true;
  __LEAVE_FUNCTION
    return false;
}

command_state_t CommandParser::parser_commandtype(const char* str) {
  __ENTER_FUNCTION
    command_state_t state;
    state.type = kCmdUnkown;
    char cmdhead[kCmdSize];
    memset(cmdhead, '\0', sizeof(cmdhead));
    uint32_t i;
    for (i = 0; i < sizeof(cmdhead) - 1; ++i) {
      char charinput = str[i];
      if (' ' == charinput || '\t' == charinput || '\0' == charinput) break;
      cmdhead[i] = str[i];
    }
    if (0 == strcmp(cmdhead, "saveall")) {
      state.type = kCmdSaveAll;
    }
    else if (0 == strcmp(cmdhead, "clearall")) {
      state.type = kCmdClearAll;
    }
    return state;
  __LEAVE_FUNCTION
}
