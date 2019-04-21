#include <graphenelib/asset.h>
#include <graphenelib/contract.hpp>
#include <graphenelib/contract_asset.hpp>
#include <graphenelib/crypto.h>
#include <graphenelib/dispatcher.hpp>
#include <graphenelib/global.h>
#include <graphenelib/multi_index.hpp>
#include <graphenelib/print.hpp>
#include <graphenelib/system.h>
#include <graphenelib/types.h>

#include<cmath>

using namespace graphene;

static const uint64_t redpacket_asset_id = 1;//GXS

class redpacket : public contract
{
  public:
    redpacket(uint64_t id)
        : contract(id)
        , users(_self, _self)
        , housechecks(_self, _self)
        ,testaments(_self,_self)
    {
    }

  
//@abi action idcardcheck
   void idcardcheck(std::string zhengHash,std::string fanHash,std::string name)
   {
       
       print("jsx:xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",zhengHash,fanHash,name,"\n");
      
       uint64_t user=get_trx_sender();
       
       print(user,"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
       auto it=users.find(user);

       if(it==users.end())
       {
            print(user,"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
           users.emplace(user,[&](auto &o){
                    o.user_id=user;
                    o.name=name;
                    o.on_hash=zhengHash;
                    o.off_hash=fanHash;
                });
             print(user,"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");  
       }
       else
       {
           users.modify(it,0,[&](auto &o){
                    o.name=name;
                    o.on_hash=zhengHash;
                    o.off_hash=fanHash;
               
           });
         }
       }
       //@abi action checkhouse
   void checkhouse(std::string hash,std::string name)
   {

       uint64_t user=get_trx_sender();
       auto it=housechecks.find(user);
        house new_house;
        new_house.name=name;
        new_house.hash=hash;
       if(it==housechecks.end())
       {
           housechecks.emplace(user,[&](auto &o){
                    o.owner=user;
                    o.houses.push_back(new_house);
                });
       }
       else
       {
           housechecks.modify(it,0,[&](auto &o){
                    o.houses.push_back(new_house);
           });
         }
       
   }
   //@abi action  intestament
    void intestament(std::string explain)
    {
        uint64_t user=get_trx_sender();
        auto it=testaments.find(user);
        if(it==testaments.end())
       {
           testaments.emplace(user,[&](auto &o){
                    o.user_id=user;
                    o.explain=explain;
                });
       }
       else
       {
           testaments.modify(it,0,[&](auto &o){
                    o.explain=explain;
           });
         }
    }
    //@abi action  deleteuser
    void  deleteuser()
    {
        uint64_t user=get_trx_sender();
        auto it_user = users.find(user);
        if(it_user!=users.end())
        {
            users.erase(it_user);
        }
        auto it_check=housechecks.find(user);
        if(it_check!=housechecks.end())
        {
            housechecks.erase(it_check);   
        }
        auto it_testament=testaments.find(user);
        if(it_testament!=testaments.end())
        {
            testaments.erase(it_testament);
        }
    }
    
    
  private:
  
//@abi table user
    struct user
    {
        uint64_t user_id;
        std::string name; 
        std::string on_hash;
        std::string off_hash;
        
        uint64_t primary_key() const{return user_id;}
        GRAPHENE_SERIALIZE(user, (user_id)(name)(on_hash)(off_hash))
    };
     typedef graphene::multi_index<N(user), user> user_index;
     user_index users;
     struct house
     {
        std::string name;
        std::string hash;
        GRAPHENE_SERIALIZE(house, (name)(hash))
     };
  //@abi table housecheck
    struct housecheck
    {
        uint64_t owner;
        std::vector<house>  houses;
        
        uint64_t primary_key() const{return owner;}
        GRAPHENE_SERIALIZE(housecheck, (owner)(houses))
    };
     typedef graphene::multi_index<N(housecheck), housecheck> housecheck_index;
    housecheck_index housechecks;
    //@abi table testament
    struct testament
    {
        uint64_t user_id;
        std::string explain;
         uint64_t primary_key() const{return user_id;}
        GRAPHENE_SERIALIZE(testament, (user_id)(explain))
    };
    typedef graphene::multi_index<N(testament), testament> testament_index;
    testament_index testaments;
 
};

GRAPHENE_ABI(redpacket,(idcardcheck)(checkhouse)(intestament)(deleteuser) )
