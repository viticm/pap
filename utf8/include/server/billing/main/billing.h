/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id billing.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2014-1-13 16:14:27
 * @uses billing server main file
 */
#ifndef PAP_SERVER_BILLING_MAIN_BILLING_H_
#define PAP_SERVER_BILLING_MAIN_BILLING_H_

class Billing {
 
 public:
   Billing();
   ~Billing();

 public:
   bool init();
   bool loop();
   bool exit();

 protected:
   bool new_staticmanager();
   bool init_staticmanager();
   bool release_staticmanager();

};

extern Billing g_billing;

#endif //PAP_SERVER_BILLING_MAIN_BILLING_H_

