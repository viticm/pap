#include "server/common/base/config.h"
#include "server/common/base/file_define.h"
#include "common/base/type.h"

pap_server_common_base::Config g_config;

namespace pap_server_common_base {

//--struct start

config_info_t::config_info_t() {
  __ENTER_FUNCTION
    global.drop_param = 2.0;
    global.equipment_damage_point = 500;
    global.respawn_param = 1;
    global.pk_refix_of_damage = 100;
    global.disciple_proffer_exp = 2;
    global.god_relive_top_level = 20;
    global.audit_switch = true;
    global.auto_remove_bad_pet = true;
    localization.language = 1;
    zone.size = 10;
    time.recover_time = 10000;
    time.disconnect_time1 = 20000;
    time.disconnect_time2 = 20000;
    time.kick_user_time = 300000;
    time.smu_kick_user_time = 1800000;
    time.drop_box_recycle = 60000;
    time.time_change_interval = 150000;
    time.packet_audit_time = 0;
    monster.max_count = 20000;
    monster.default_respawn_time = 30000;
    monster.default_position_range = 10;
    monster.default_ai_type = 1;
    monster.default_body_time = 5000;
    monster.default_boss_body_time = 3000;
    monster.odds_of_change_target = 20;
    monster.odds_of_attack_assistant = 16;
    monster.change_target_cooldown = 3;
    monster.default_max_level = 150;
    portal.max_count = 1024;
    platform.max_count = 1024;
    skill_obj.max_count = 1024;
    special_obj.max_count = 1024;
    bus_obj.max_count = 1024;
    player_shop.max_count = 100;
    player_shop.payment_per_hour = 0;
    scene_timer.max_count = 64;
    human_timer.max_count = 3;
    pet.max_count = 1000;
    pet.body_time = 2000;
    pet.happiness_interval = 600000;
    pet.life_interval = 600000;
    pet.dec_life_step = 7;
    pet.call_up_happiness = 60;
    pet.placard_time = 1800000;
    pet.placard_need_level = 30;
    pet.placard_need_happiness = 100;
    pet.placard_need_life = 3000;
    pet.compound_gen_gu_float = 5;
    pet.compound_grow_float = 5;
    pet.compound_baby_per_wild_with_wild = 10;
    pet.compound_baby_per_baby_with_baby = 95;
    pet.compound_baby_per_wild_with_baby = 30;
    pet.compound_perception_per = 70;
    pet.default_max_level = 115;
    pet.die_lreduce_life = 0.4;
    human.can_get_exp_range = 60;
    human.out_ghost_time = 300000;
    human.default_move_speed = 5000;
    human.default_attack_speed = 2000;
    human.default_refresh_rate = 60000;
    human.energy_vigor_recover_interval = 300000;
    human.default_max_level = 119;
    human.pk_value_refresh_rate = 3600;
    human.default_pilfer_lock_time = 6000;
    human.default_xinfa_max_level = 150;
    human.level_up_validate_min_level = 0;
    human.level_up_validate_min_level = 20;
    human.can_get_yuanbao_ticket_min_level = 30;
    team.available_follow_dist = 10;
    team.time_for_lose_follow = 30;
    guild.found_duration = 24;
    guild.default_max_member_count = 36;
    guild.response_user_count = 2;
    memset(guild.xianya_max_user, 0, sizeof(guild.xianya_max_user));
    memset(guild.xianya_standard_money, 0, sizeof(guild.xianya_standard_money));
    memset(guild.xianya_max_money, 0, sizeof(guild.xianya_max_money));
    memset(guild.xianya_max_trader, 0, sizeof(guild.xianya_max_trader));
    memset(guild.bank_standard_money, 0, sizeof(guild.bank_standard_money));
    memset(guild.wing_max_user, 0, sizeof(guild.wing_max_user));
    guild.create_city_money = 10000000;
    guild.leave_word_cost = 1000;
    guild.battle_time = 120;
    guild.left_guild_buff_enable = true;
    guild.boom_max_value = 999;
    guild.boom_scale_all = 1;
    guild.boom_scale_online_count = 0.6;
    guild.boom_scale_attribute_increase = 0.15;
    guild.boom_scale_trader_transactions_count = 1;
    guild.boom_scale_avg_boom = 0.06;
    guild.boom_scale_dilation = 0.4;
    guild.boom_scale_farming = 1.6;
    guild.boom_scale_trading_mission = 1.6;
    guild.boom_scale_defence = 0.8;
    guild.boom_scale_industry = 1.6;
    guild.boom_scale_technology = 0.8;
    guild.trade_ticket_decrease_value = 136;
    guild.trading_mission_plug = true;
    guild.validate_xianya_level = true;
    guild_league.max_count = 255;
    guild_league.quit_league_wait_time = 72;
    guild_league.create_money = 1000000;
    relation.password_point = 500;
    relation.prompt_point = 0;
    relation.get_point_need_exp = 1;
    minor_password.unlock_delay_time = 24;
    minor_password.energy_set_cost = 20;
    minor_password.energy_modify_cost = 20;
    minor_password.energy_unlock_cost 100;
    minor_password.input_error_times_per_day = 5;
    minor_password.password_unlock_time = 24;
    world.hash_online_user_count = 2000;
    world.hash_mail_user_count = 30000;
    world.max_offline_user_count = 50000;
    world.speaker_pool_max = 128;
    memset(temp.user_path,'\0', sizeof(temp.user_path));
    combat.default_damage_fluctuation = 8;
    combat.h0_of_hit_calculation = 10;
    combat.c0_of_critical_calculation = 100;
    combat.c1_of_critical_calculation = 10;
    combat.c2_of_critical_calculation = 25;
    good_and_evil.min_value = 0;
    good_and_evil.max_value = 1000000;
    good_and_evil.get_value_need_level = 20;
    good_and_evil.give_value_min_level = 10;
    good_and_evil.give_value_max_level = 40;
    good_and_evil.give_value_difference_level = 8;
    good_and_evil.give_value_radius = 15;
    good_and_evil.per_member_give_value = 5;
    good_and_evil.per_disciple_give_value = 3;
    good_and_evil.once_max_give_value = 2;
    good_and_evil.member_die_cost_value = 100;
    plot_point.min = 0;
    plot_point.max = 9999;
    economic.rate_a = 0.25;
    economic.rate_b = 0.1;
    economic.yuanbao_transaction_scene_id = 0;
    economic.yuanbao_ticket_max = 10000;
    economic.new_server_sale_rate = 1.0;
    economic.min_exchange_code_level = 15;
    economic.max_exchange_code_level = 25;
    exp.revise_param = 1.0;
    exp.team_spouse_add_rate = 0.04;
    exp.team_brother_add_rate = 0.02;
    exp.team_master_in_add_rate = 0.2;
    exp.team_master_notin_add_rate = 0.1;
    exp.team_disciple_add_rate = 0.05;
    exp.hidden_or_magic_weapon_absorb_rate = 0.01;
    duel.continue_time = 600;
    duel.need_min_level = 10;
    duel.need_energy = 100;
    warfare.continue_time = 600;
    pk.flag_switch_delay = 600;
    pk.hostile_player_warning = 30;
    memset(ability.assistant_demand_formula_param, 0, sizeof(ability.assistant_demand_formula_param));
    fatigue.enable = false;
    fatigue.little_fatigue_time = 10800;
    fatigue.exceeding_fatigue_time = 18000;
    fatigue.reset_fatigue_state_offline_time = 18000;
    yuanbao.max_day_can_cost = 167772150;
    yuanbao.enable_exchage_yuanbao_ticket = true;
    monster_income.little_count = 7000;
    monster_income.nil_count = 10000;
    monster_income.little_percent = 0.5;
    commision_shop.max_count = 10; //max write in code, can't read in config file
    commision_shop.send_back_time = 360;
    commision_shop.yuanbao_fee = 2;
    commision_shop.gold_coin_fee = 2;
    memset(commision_shop.yuanbao_value, 0, sizeof(commision_shop.yuanbao_value));
    memset(commision_shop.gold_coin_value, 0, sizeof(commision_shop.gold_coin_fee));
  __LEAVE_FUNCTION
}

config_info_t::~config_info_t() {
  //do nothing
}

login_info_t::login_info_t() {
  __ENTER_FUNCTION
    login_id = ID_INVALID; 
    memset(db_ip, '\0', sizeof(db_ip));
    db_port = 3306; //default mysql port
    memset(db_name, '\0', sizeof(db_name));
    memset(db_connection_name, '\0', sizeof(db_connection_name));
    memset(db_user, '\0', sizeof(db_user));
    memset(db_password, '\0', sizeof(db_password));
    odbc_switch = true;
    db_type = -1;
    encrypt_password = false;
    client_version = 0;
    db_connect_count = 1;
    turn_player_count = 100;
    proxy_connect = 0;
    enable_license = false
    relogin_limit = false;
    relogin_stop = false;
    relogin_stop_time = 60000;
    notify_safe_sign = false;
  __LEAVE_FUNCTION
}

login_info_t::~login_info_t() {
  //do nothing
}

billing_data_t::billing_data_t() {
  __ENTER_FUNCTION
    memset(ip, '\0', sizeof(ip));
    port = 3306;
    container_postion = -1;
  __LEAVE_FUNCTION
}

billing_data_t::~billing_data_t() {
  //do nothing
}

world_info_t::world_info_t() {
  __ENTER_FUNCTION
    id = ID_INVALID;
    zone_id = ID_INVALID;
    share_memory_key.guild = 0;
    share_memory_key.mail = 0;
    share_memory_key.pet = 0;
    share_memory_key.city = 0;
    share_memory_key.global_data = 0;
    share_memory_key.league = 0;
    share_memory_key.find_friend = 0;
    enable_share_memory = true;
  __LEAVE_FUNCTION
}

world_info_t::~world_info_t() {
  //do nothing
}

share_memory_key_data_t::share_memory_key_data_t() {
  __ENTER_FUNCTION
    key = 0;
    type = 0;
  __LEAVE_FUNCTION
}

share_memory_key_data_t::~share_memory_key_data_t() {
  //do nothing
}

share_memory_info_t::share_memory_info_t() {
  __ENTER_FUNCTION
    key_data = NULL;
    obj_count = 0;
    memset(db_ip, '\0', sizeof(db_ip));
    db_port = 3306; //default mysql port
    memset(db_name, '\0', sizeof(db_name));
    memset(db_connection_name, '\0', sizeof(db_connection_name));
    memset(db_user, '\0', sizeof(db_user));
    memset(db_password, '\0', sizeof(db_password));
    odbc_switch = true;
    db_type = -1;
    encrypt_password = false;
    world_data_save_interval = 1200000;
    human_data_save_interval = 900000;;
  __ENTER_FUNCTION
}

share_memory_info_t::~share_memory_info_t() {
  __ENTER_FUNCTION
    SAFE_DELETE_ARRAY(key_data);
  __LEAVE_FUNCTION
}

machine_data_t::machine_data_t() {
  __ENTER_FUNCTION
    id = ID_INVALID;
  __LEAVE_FUNCTION
}

machine_data_t::~machine_data_t() {
  //do nothing
}

machine_info_t::machine_info_t() {
  __ENTER_FUNCTION
    data = NULL;
    count = 0;
  __LEAVE_FUNCTION
}

machine_info_t::~machine_info_t() {
  __ENTER_FUNCTION
    SAFE_DELETE_ARRAY(data);
    count = 0;
  __LEAVE_FUNCTION
}

proxy_data_t::proxy_data_t() {
  __ENTER_FUNCTION
    isp = kIspInvalid;
    memset(ip, '\0', sizeof(ip));
    port = 0;
    enable = false;
  __LEAVE_FUNCTION
}

proxy_data_t::~proxy_data_t() {
  //do nothing
}

server_data_t::server_data_t() {
  __ENTER_FUNCTION
    id = ID_INVALID;
    machine_id = ID_INVALID;
    memset(ip0, '\0', sizeof(ip0));
    port0 = 0;
    memset(ip1, '\0', sizeof(ip1));
    port1 = 0;
    type = -1;
    share_memory_key.human = 0;
    share_memory_key.player_shop = 0;
    share_memory_key.item_serial = 0;
    share_memory_key.commision_shop = 0;
    enable_share_memory = false;
  __LEAVE_FUNCTION
}

server_data_t::~server_data_t() {
  //do nothing
}

server_info_t::server_info_t() {
  __ENTER_FUNCTION
    data = NULL;
    count = 0;
    current_server_id = -1;
    memset(world_data.ip, '\0', sizeof(world_data.ip));
  __LEAVE_FUNCTION
}

server_data_t::~server_info_t() {
  //do nothing
}

scene_data_t::scene_data_t() {
  __ENTER_FUNCTION
    thread_index = INDEX_INVALID;
    client_resource_index = INDEX_INVALID;
    id = ID_INVALID;
    active = false;
    memset(name, '\0', sizeof(name));
    memset(file_name, '\0', sizeof(file_name));
    server_id = ID_INVALID;
    type = -1;
    pvp_ruler = 0;
    begin_plus = 0;
    plus_client_resource_index = -1;
    end_plus = 0;
    relive = false;
  __LEAVE_FUNCTION
}

scene_data_t::~scene_data_t() {
  //do nothing
}

scene_info_t::scene_info_t() {
  __ENTER_FUNCTION
    data = NULL;
    count = 0;
    memset(scene_hash, -1, sizeof(scene_hash));
  __LEAVE_FUNCTION
}

scene_info_t::~scene_info_t() {
  //do nothing
}

internal_ip_of_proxy_t::internal_ip_of_proxy_t{
  __ENTER_FUNCTION
    memset(proxy_for_cnc_user, '\0', sizeof(proxy_for_cnc_user));
    memset(proxy_for_ctc_user, '\0', sizeof(proxy_for_ctc_user));
    memset(proxy_for_edu_user, '\0', sizeof(proxy_for_edu_user));
  __LEAVE_FUNCTION
}

internal_ip_of_proxy_t::~internal_ip_of_proxy_t() {
  //do nothing
}

enum_isp internal_ip_of_proxy_t::ip_from(const char* ip) {
  __ENTER_FUNCTION
    uint32_t i;
    for (i = 0; kProxyForOneNetworkMax > i; ++i) {
      if (0 == strncmp(ip, proxy_for_cnc_user[i], IP_SIZE)) {
        return kIspChinaNetCom;
      }
      else if (0 == strncmp(ip, proxy_for_ctc_user[i], IP_SIZE)) {
        return kIspChinaTeleCom;
      }
      else if (0 == strncmp(ip, proxy_for_edu_user[i], IP_SIZE)) {
        return kIspChinaEdu;
      }
    }
  __LEAVE_FUNCTION
}

//struct end--

//-- class start

BillingInfo::BillingInfo() {
  __ENTER_FUNCTION
    info_pool_ = NULL;
    number_ = 0;
    current_billing_no_ = 0;
    can_use_ = false;
    memset(ip_, '\0', sizeof(ip));
    port_ = 0;
  __LEAVE_FUNCTION
}

BillingInfo::~BillingInfo() {
  __ENTER_FUNCTION
    clean_up();
  __LEAVE_FUNCTION
}

void BillingInfo::clean_up() {
  __ENTER_FUNCTION
    if (info_pool_ && number_ > 0) {
      uint32_t i;
      for (i = 0; i < number_; ++i) {
        SAFE_DELETE(info_pool_[i]);
      }
    }
    SAFE_DELETE_ARRAY(info_pool_);
    memset(ip_, '\0', sizeof(ip_));
    number_ = 0;
    current_billing_no_ = 0;
    can_use_ = false;
  __LEAVE_FUNCTION
}

bool BillingInfo::init(uint16_t number) {
  __ENTER_FUNCTION
    pap_common_base::Assert(number > 0);
    number_ = number;
    info_pool_ = new billing_data_t*[number_];
    pap_common_base::Assert(info_pool_);
    uint32_t i;
    for (i = 0; i < number_; ++i) {
      info_pool_[i] = new billing_data_t();
      info_pool_[i].container_postion = i;
    }
  __LEAVE_FUNCTION
    return false;
}

uint16_t BillingInfo::get_number() {
  __ENTER_FUNCTION
    return number_
  __LEAVE_FUNCTION
    return 0;
}

billing_data_t* BillingInfo::next() {
  __ENTER_FUNCTION
    billing_data_t* current = info_pool_[current_billing_no_];
    current_billing_no_ = (current_billing_no_ + 1) >= number_ ? 0 : current_billing_no_ + 1;
    return current;
  __LEAVE_FUNCTION
}

void BillingInfo::begin_use() {
  __ENTER_FUNCTION
    current_billing_no_ = 0;
    used_ = true;
    if (info_pool_) {
      billing_data_t current = info_pool_[current_billing_no_];
      port_ = current->port;
      snprintf(ip_, strlen(current->ip),"%s", current->ip);
    }
  __LEAVE_FUNCTION
}

bool BillingInfo::is_use() {
  __ENTER_FUNCTION
    return used_;
  __LEAVE_FUNCTION
    return false;
}

Config::Config() {
  //do nothing
}

Config::~Config() {
  //do noting
}

bool Config::init() {
  __ENTER_FUNCTION
    load_config_info();
    load_login_info();
    load_world_info();
    load_billing_info();
    load_share_memory_info();
    load_machine_info();
    load_server_info();
    load_scene_info();
    load_copy_scene_info();
    return true;
  __LEAVE_FUNCTION
    return false;
}

void Config::reload() {
  __ENTER_FUNCTION
    load_config_info_reload();
    load_login_info_reload();
    load_world_info_reload();
    load_billing_info_reload();
    load_share_memory_info_reload();
    load_machine_info_reload();
    load_server_info_reload();
    load_scene_info_reload();
    load_copy_scene_info_reload();
  __LEAVE_FUNCTION
}

void Config::load_config_info() {
  __ENTER_FUNCTION
    load_config_info_only();
    load_config_info_reload();
  __LEAVE_FUNCTION
}

void Config::load_config_info_only() { //this params just read once
  __ENTER_FUNCTION
    Ini config_info_ini(CONFIG_INFO_FILE);
    int32_t value;
    config_info_.zone.size = config_info_ini.read_uint8("Zone", "Size");
    config_info_.portal.max_count = config_info_ini.read_uint16("Portal", "MaxCount");
    config_info_.platform.max_count = config_info_ini.read_uint16("Platform", "MaxCount");
    config_info_.skill_obj.max_count = config_info_ini.read_uint16("SkillObj", "MaxCount");
    config_info_.special_obj.max_count = config_info_ini.read_uint16("SpecialObj", "MaxCount");
    config_info_.bus_obj.max_count = config_info_ini.read_uint16("BusObj", "MaxCount");
    config_info_.player_shop.max_count = config_info_ini.read_uint16("PlayerShop", "MaxCount");
    config_info_.scene_timer.max_count = config_info_ini.read_uint16("SceneTimer","MaxCount");
    config_info_.human_timer.max_count = config_info_ini.read_uint16("HumanTimer","MaxCount");
  __LEAVE_FUNCTION
}

//class end --

} //namespace pap_server_common_base
