-- GraphPlot.wlua
-- Plot any Lua expression in two variables x and y
-- Junfeng Liu @ 2011-06-27

require"cdlua"
require"iuplua"
require"iupluacd"

setmetatable(_G, { __index = math })
e = exp(1)

-- Load Config and Favorites
dofile("Favorites.lua")
pixels = {}
for r=1,Config.Height do
  pixels[r] = {}
  for c=1,Config.Width do
        pixels[r][c] = false
  end
end

cnv = iup.canvas{ rastersize=string.format("%dx%d", Config.Width, Config.Height) }
treeFavorite = iup.tree{ size = "100x100"}

canvasColor = cd.EncodeColor(255,255,255)
penColor = cd.EncodeColor(0,0,0)

function selectColor(self)
  r,g,b = iup.GetColor(iup.CENTER,iup.CENTER)
 self.bgcolor = string.format("%d %d %d",r,g,b)
 if self.name == "btnPen" then penColor = cd.EncodeColor(r,g,b)
 else canvasColor = cd.EncodeColor(r,g,b) end
end

dlg = iup.dialog
{
    title="Plot graphs of equations and inequalities in two vairables",
    resize="NO",
    minbox="NO",
    iup.hbox
    {
        iup.vbox
        {
           iup.frame
           {
               title = "Color",
               iup.hbox
               {
                    iup.label{title = " Canvas: "},
                    iup.button{ name = "btnCanvas", size = "22x10", bgcolor="255 255 255", flat="YES", action = selectColor},
                    iup.label{title = " Pen: "},
                    iup.button{ name = "btnPen", size = "22x10", bgcolor="0 0 0", flat="YES", action = selectColor},
                    alignment = "ACENTER"
               }
           },
           iup.frame
           {
               title = "Range",
               iup.vbox
               {
                    iup.hbox
                    {
                        iup.label{title = "X: "},
                        iup.text{ name = "txtXMin", size = "38x10", value = Config.Xmin},
                        iup.label{title = " ~ "},
                        iup.text{ name = "txtXMax", size = "38x10", value = Config.Xmax}
                    },
                    iup.hbox
                    {
                        iup.label{title = "Y: "},
                        iup.text{ name = "txtYMin", size = "38x10", value = Config.Ymin},
                        iup.label{title = " ~ "},
                        iup.text{ name = "txtYMax", size = "38x10", value = Config.Ymax}
                    }
               }
           },
           iup.hbox
           {
                iup.label{ title = "Pixel Split: " },
                iup.text{ name = "txtSplit", value = Config.Split},
                alignment = "ACENTER"
           },
           treeFavorite,
           margin = "2x2"
        },
        iup.vbox
        {
            iup.hbox
            {
                iup.label{title = "Expression: "},
                iup.text{ name = "exprtext", rastersize = (Config.Width-120).."x22", value = "abs(x - y) % 20 < 0.0001"},
                iup.button{title = "Plot", size = "34x12", action = function() plotExpression() end},
                alignment = "ACENTER"
            },
            cnv,
            margin = "2x2"
        }
    }
}

function getNumber(name)
    return tonumber(iup.GetDialogChild(dlg, name).value)
end

function setTextValue(name, value)
    iup.GetDialogChild(dlg, name).value = value
end

function plotExpression()
    local expr = iup.GetDialogChild(dlg, "exprtext").value
    local func, err = loadstring("return function (x,y) return ".. expr.." end")
    if func==nil then iup.Message("Error", "Expression has syntax errors:\r\n"..err) return end
    equation = func()
    drawing = true
    iup.Redraw(cnv, 0)
end

function cnv:map_cb()
  canvas = cd.CreateCanvas(cd.IUP, self)
end

drawing = false
function cnv:action()
  canvas:Activate()
  canvas:Background(canvasColor)
  canvas:Clear()
  local width = Config.Width
  local height = Config.Height
  if drawing == false then
    for r=height,1,-1 do
      for c=1,width do
          if pixels[r][c] then
            canvas:Pixel(c, r, penColor)
          end
      end
    end
    return
  end

  dlg.active = "NO"
  local xMin = getNumber("txtXMin")
  local xMax = getNumber("txtXMax")
  local yMin = getNumber("txtYMin")
  local yMax = getNumber("txtYMax")
  local split = getNumber("txtSplit")
  local DX = (xMax - xMin)/width
  local DY = (yMax - yMin)/height
  local dx = DX / split
  local dy = DY / split
  local x = xMin
  local y = yMax
  for r=height,1,-1 do
      for c=1,width do
        local fill = isSolution(x,y,dx,dy,split)
        pixels[r][c] = fill
        if fill then
            canvas:Pixel(c, r, penColor)
        end
        x = x + DX
      end
      x = xMin
      y = y - DY
  end
  drawing = false
  dlg.active = "YES"
end

function isSolution(x0,y0,dx,dy,split)
    local x = x0
    local y = y0
    for i=1,split do
        for j=1,split do
            if equation(x, y) then return true end
            x = x + dx
        end
        x = x0
        y = y - dy
    end
    return false
end

function treeFavorite:selection_cb(id, status)
    if status == 1 then
        node = Favorites[id]
        setTextValue("exprtext", node.tip)
        if node.config ~= nil then
            setTextValue("txtXMin", node.config.Xmin)
            setTextValue("txtXMax", node.config.Xmax)
            setTextValue("txtYMin", node.config.Ymin)
            setTextValue("txtYMax", node.config.Ymax)
            setTextValue("txtSplit", node.config.Split)
        end
    end
end

function dlg:close_cb()
  canvas:Kill()
  self:destroy()
  return iup.IGNORE
end

dlg:show()
iup.TreeAddNodes(treeFavorite, Favorites)
iup.MainLoop()