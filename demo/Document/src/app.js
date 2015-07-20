
var HelloWorldLayer = cc.Layer.extend({
    sprite:null,
    ctor:function () {

        this._super();

        var winSize = cc.winSize;

        {
            var text = new ccui.Text("show alert", "Marker Felt.ttf", 28);
            text.setTouchEnabled(true);
            text.setPosition(winSize.width / 2,winSize.height / 2);
            text.addTouchEventListener(function(sender,type)
                {
                    if (ccui.Widget.TOUCH_ENDED != type) return ;
                    var param = {
                                "title" : "Welcome",
                                "message" : "this is a js scene",
                                "leftbtn" : "Ok"
                                };
                    VCT.Channel.Request("alertmodule","show",JSON.stringify(param),function(args)
                    {
                        cc.log(args);
                    });
                });
            this.addChild(text);
        }

        {
            var text = new ccui.Text("back to cpp scene", "Marker Felt.ttf", 28);
            text.setTouchEnabled(true);
            text.setPosition(100,100);
            text.addTouchEventListener(function(sender,type)
                {
                    if (ccui.Widget.TOUCH_ENDED != type) return ;
                    VCT.Channel.Request("handlemodule","trigger","tocppscene","");
                });
            this.addChild(text);
        }

        VCT.Channel.Request("handlemodule","register","tojsscene",function(args)
        {
            cc.director.runScene(new HelloWorldScene());
        });

        return true;
    }
});

var HelloWorldScene = cc.Scene.extend({
    onEnter:function () {
        this._super();
        var layer = new HelloWorldLayer();
        this.addChild(layer);
    }
});

