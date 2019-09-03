from pyecharts.charts import Geo 
data =[("海门", 9), ("鄂尔多斯", 12), ("招远", 12), ("舟山", 12), ("齐齐哈尔", 14), ("盐城", 15)]
geo =Geo("全国主要城市空气质量", "data from pm2.5", title_color="#fff", title_pos="center", width=1200, height=600, background_color='#404a59')
attr, value =geo.cast(data)
geo.add("", attr, value, type="effectScatter", is_random=True, effect_scale=5)
geo.show_config()
geo.render()