 1 -- GraphPlot.wlua
  2 -- Plot any Lua expression in two variables x and y
  3 -- Junfeng Liu @ 2011-06-27
  4 
  5 require"cdlua"
  6 require"iuplua"
  7 require"iupluacd"
  8 
  9 setmetatable(_G, { __index = math })
 10 e = exp(1)
 11 
 12 -- Load Config and Favorites
 13 dofile("Favorites.lua")
 14 pixels = {}
 15 for r=1,Config.Height do
 16   pixels[r] = {}
 17   for c=1,Config.Width do
 18         pixels[r][c] = false
 19   end
 20 end
 21 
 22 cnv = iup.canvas{ rastersize=string.format("%dx%d", Config.Width, Config.Height) }
 23 treeFavorite = iup.tree{ size = "100x100"}
 24 
 25 canvasColor = cd.EncodeColor(255,255,255)
 26 penColor = cd.EncodeColor(0,0,0)
 27 
 28 function selectColor(self)
 29   r,g,b = iup.GetColor(iup.CENTER,iup.CENTER)
 30  self.bgcolor = string.format("%d %d %d",r,g,b)
 31  if self.name == "btnPen" then penColor = cd.EncodeColor(r,g,b)
 32  else canvasColor = cd.EncodeColor(r,g,b) end
 33 end
 34 
 35 dlg = iup.dialog
 36 {
 37     title="Plot graphs of equations and inequalities in two vairables",
 38     resize="NO",
 39     minbox="NO",
 40     iup.hbox
 41     {
 42         iup.vbox
 43         {
 44            iup.frame
 45            {
 46                title = "Color",
 47                iup.hbox
 48                {
 49                     iup.label{title = " Canvas: "},
 50                     iup.button{ name = "btnCanvas", size = "22x10", bgcolor="255 255 255", flat="YES", action = selectColor},
 51                     iup.label{title = " Pen: "},
 52                     iup.button{ name = "btnPen", size = "22x10", bgcolor="0 0 0", flat="YES", action = selectColor},
 53                     alignment = "ACENTER"
 54                }
 55            },
 56            iup.frame
 57            {
 58                title = "Range",
 59                iup.vbox
 60                {
 61                     iup.hbox
 62                     {
 63                         iup.label{title = "X: "},
 64                         iup.text{ name = "txtXMin", size = "38x10", value = Config.Xmin},
 65                         iup.label{title = " ~ "},
 66                         iup.text{ name = "txtXMax", size = "38x10", value = Config.Xmax}
 67                     },
 68                     iup.hbox
 69                     {
 70                         iup.label{title = "Y: "},
 71                         iup.text{ name = "txtYMin", size = "38x10", value = Config.Ymin},
 72                         iup.label{title = " ~ "},
 73                         iup.text{ name = "txtYMax", size = "38x10", value = Config.Ymax}
 74                     }
 75                }
 76            },
 77            iup.hbox
 78            {
 79                 iup.label{ title = "Pixel Split: " },
 80                 iup.text{ name = "txtSplit", value = Config.Split},
 81                 alignment = "ACENTER"
 82            },
 83            treeFavorite,
 84            margin = "2x2"
 85         },
 86         iup.vbox
 87         {
 88             iup.hbox
 89             {
 90                 iup.label{title = "Expression: "},
 91                 iup.text{ name = "exprtext", rastersize = (Config.Width-120).."x22", value = "abs(x - y) % 20 < 0.0001"},
 92                 iup.button{title = "Plot", size = "34x12", action = function() plotExpression() end},
 93                 alignment = "ACENTER"
 94             },
 95             cnv,
 96             margin = "2x2"
 97         }
 98     }
 99 }
100 
101 function getNumber(name)
102     return tonumber(iup.GetDialogChild(dlg, name).value)
103 end
104 
105 function setTextValue(name, value)
106     iup.GetDialogChild(dlg, name).value = value
107 end
108 
109 function plotExpression()
110     local expr = iup.GetDialogChild(dlg, "exprtext").value
111     local func, err = loadstring("return function (x,y) return ".. expr.." end")
112     if func==nil then iup.Message("Error", "Expression has syntax errors:\r\n"..err) return end
113     equation = func()
114     drawing = true
115     iup.Redraw(cnv, 0)
116 end
117 
118 function cnv:map_cb()
119   canvas = cd.CreateCanvas(cd.IUP, self)
120 end
121 
122 drawing = false
123 function cnv:action()
124   canvas:Activate()
125   canvas:Background(canvasColor)
126   canvas:Clear()
127   local width = Config.Width
128   local height = Config.Height
129   if drawing == false then
130     for r=height,1,-1 do
131       for c=1,width do
132           if pixels[r][c] then
133             canvas:Pixel(c, r, penColor)
134           end
135       end
136     end
137     return
138   end
139 
140   dlg.active = "NO"
141   local xMin = getNumber("txtXMin")
142   local xMax = getNumber("txtXMax")
143   local yMin = getNumber("txtYMin")
144   local yMax = getNumber("txtYMax")
145   local split = getNumber("txtSplit")
146   local DX = (xMax - xMin)/width
147   local DY = (yMax - yMin)/height
148   local dx = DX / split
149   local dy = DY / split
150   local x = xMin
151   local y = yMax
152   for r=height,1,-1 do
153       for c=1,width do
154         local fill = isSolution(x,y,dx,dy,split)
155         pixels[r][c] = fill
156         if fill then
157             canvas:Pixel(c, r, penColor)
158         end
159         x = x + DX
160       end
161       x = xMin
162       y = y - DY
163   end
164   drawing = false
165   dlg.active = "YES"
166 end
167 
168 function isSolution(x0,y0,dx,dy,split)
169     local x = x0
170     local y = y0
171     for i=1,split do
172         for j=1,split do
173             if equation(x, y) then return true end
174             x = x + dx
175         end
176         x = x0
177         y = y - dy
178     end
179     return false
180 end
181 
182 function treeFavorite:selection_cb(id, status)
183     if status == 1 then
184         node = Favorites[id]
185         setTextValue("exprtext", node.tip)
186         if node.config ~= nil then
187             setTextValue("txtXMin", node.config.Xmin)
188             setTextValue("txtXMax", node.config.Xmax)
189             setTextValue("txtYMin", node.config.Ymin)
190             setTextValue("txtYMax", node.config.Ymax)
191             setTextValue("txtSplit", node.config.Split)
192         end
193     end
194 end
195 
196 function dlg:close_cb()
197   canvas:Kill()
198   self:destroy()
199   return iup.IGNORE
200 end
201 
202 dlg:show()
203 iup.TreeAddNodes(treeFavorite, Favorites)
204 iup.MainLoop()