# ascii_converter

Converts an arbitrary image into ascii.

Determines ascii characters by finding the glyph that most closely represents
the laplacian of the image in each character sized region. This results in fairly
high quality ascii output for most images which aren't excessively complex.

```
Usage: usage: ./main imgpath [fontsize [usecolor]]
```

Higher <code>usecolor</code> values correspond to brighter colors.

A fontsize of 10 is recommended, since other values currently have poor behavior.

###### Requires
CImg (<code>cimg-dev</code> on Ubuntu)

#### Example
```                                                                                       
                                                                                       
                                                __>==<_                                
                                             _w@`      #                               
                                           _#`-      *  |                              
                                          #`^          @`                              
                                         ^#     _,=mg`@"                               
                                      >@[    ,*` __g @`_g                              
                                    _5    _g#^^#^   ^|_-"__                            
                                  _#5_   #"   ">*^^g #  **                             
                                _#` #` `p_   _^    @     ^`|                           
                               #_g_*  _*__  y_,    #    g^@`                           
                              #"  #   #^` k_[m[   _"   #  '                            
                                      @,# ^|_*   _"   ## /                             
                                       # g  =q__@[==<#@'/                              
                                        ^_<           `_#                              
                                          <^g      _y>=@mmm==&_                        
                                           @q^=<___g>==m*mgg_&#                        
                                          _@ ^#gwr-^^^^^^"                             
                                         @[@  *_@=                                     
                                         $_#_   #_^<_                                  
                                        #` e,=_  _q, ^w_                               
                                       *^^#_@w,m,  g  $_#__p_                          
                                      0__   ^& >@g  ,#/ #" __# _                       
                                     #   @#<_ ^   ^ehu_f   ^^` _`g                     
                                     [   ,  @m_k__, & @       #^^^m,                   
                                    #       #*^`  `^&$@        =^_`[                   
                                    [       $        #^#p&__ ` #7`@                    
                   _@,      _&=*^7``       _@       ~@  @  ^^^^"`  #                   
                 g@` ^<__>*7       @       __&_^_g`  #' @   |___  ~,$                  
                  =    ,`           ,         `7^,@@^y  #   [`    _#`                  
                   $  y             g            ^__^  #` _* __#=^`                    
                   @ ''             @g              #`_^@^[@'                          
                   @ \               _^=&&_______>=*^^`  #@"                           
                    |#                =__  ^=_        _."#`                            
                     @,                       `^=g___&##"                              
                      ^,  ,                       g*`                                  
                       ^q*g^<_  __              #^                                     
                         ^@  ._k   '       __=#^^<                                     
                           |    |^**m**^^"` ^g     m_                                  
                           $    #             ^_     ^m&p=~=mmmmmmmm====>1__           
                   ______11#     k             _#_       `                  ^|         
          __u=mm^^``       @     ^`^g          $  *-                       _*          
        #^`             ,           @           =_ `                       (           
         &_                        _*             *q_                   _#^            
          ^g                     _@"                 ^&_        _g##*^^`               
        #gp___g__    ,r e _>~--____ppggg#               `^=w&&#^`                      
                 ``^^=&__  _g#^`                                                       
                        ```                                                            
```
```                                       _                                  
                                    ^ ___ @                                  
                                   m [`~ `@                                  
                                   m _ #@_@                                  
                                   m m#_#*@                                  
                                     |    #                                  
                          /"_~=__ __,@mwm0@g____,_                           
                        _@#0~`^^##===&___#=~=u~^@^#m|                        
                       *_l#        _>  ~ _<_    , ^_ ^                       
                      ##>_#^~m    `g#@#_##q@    0#*-*_*                      
                     *>^@'#`  }mg___m>u,~we__p#^,   ^@h^_                    
                   ,_^  ]#   #>g _   __a-__ _   |    b  @>,                  
                  _#`` @     @k ^   ^`  " "   _ 0         @>                 
                 _0  _#`*__<"  #,=#`=^=*==^ &*p" *__@ ^p\" @\                
                (0 ]@`,i| `    @lp~==#=#=g=*=g*,  ,`_,   \* [i               
               #   \@   *-_    [e| e~$   $,# ' l  k*^p_@j _\$@               
               [ \  @,   _  ,+ @rmw=wmmmme~wme#    \  _,^ ^ # $              
              /|  | $| `r     \@_|_/       _ __     ^-$_ p h# @i             
              '$  *@`p _     \_r `=*_g&=<q&# ` p     ^ *'#  #  @_            
             m @   $$[#_  '  @^ @"  m^^^^mr     *    4#'$ , @   @_           
              , p  [__m    _@'##`  , ^, _"       g    ^`^_   |   `h,         
              [ #   ^,      /#       _` _       [@        g  #     @<        
              #  p   ^_   \@ 0     #_`  @_+     $ |    ,   g  h      #_      
               , ^     g           ("    ^@,    | [^        g  k      @#,    
               $  g     <  \[y4    `   `_  $   _  [ \   |    g  k    `,^@_   
               @   ,     ^_@$  *_#* " g  >  p_@'     |  ^     g  h    #,*@_  
                $  *       # # $`_  ,_.<  ^_ _=_m ^, ^   \     <  h    &~_@  
                @   $     #_ _y m`g ^   *   ,|_*@  ^_ p   _     ^_ k   gg__$ 
                 |   c   @ [=_ "@  g *   ^,  [ -,*k p*     ,   __ep _ m    @ 
                 #       $#' @h  ,  < ,   ^, $_ \^ *" **   ^  @`^g |pq |     
                  ,     _$b     6 -  \^    ^_@_     @***=#g_h )   g@  p[     
                  *  _#^`$$    ^p  ", _| _  ^,@,    #      `#_[    ^| ^[     
                   |_[_#^^5  m*g __  _#^``^*<^,@    $        ^g        `     
                    &_|      $  ^g *#`        @|$   [                        
                     `*     @                    , @                         
                         #^*#                    |^_h                        
                        __  |                    @  @_                       
                       _[`*@|                    @ ` @_                      
             ___ggw=w==$____#====wgg_____g======*#____#~==gg__.              
                     ``  ``  `               ````  ``` `                     
```