#Paralela

Computación Paralela 2016

Cátedra: Lorna Figueroa Morales

Temas de investigación: 
1. Mallas de simulación de líquidos.
2. Sistemas concurrentes.
3- Algoritmos paralelos.

Tema principal:
Refinamiento de mallas triangulares mediante método bisección 4T Rivara.
Uso de mesh, showme, partdmesh, metis, .ele, .node, .mesh.

Ayudantía: Leonardo Jofré Flor
1. Tareas 1,2,3,4.
(Bcast, gather, Scatter)
Uso de mpi4py, python, mpi, c, recv & send.

Pd: creando nuevamente toda la carpeta Paralela por un force mal usado que borro todo lo que había en el repositorio.

Cátedra programada, 4T Rivara completo, bisección completa, conformidad completa, uso de Showme, uso de Verifi Conformidad ok...


DIA 1

select
	item1_desc as Item_Name,
	old_nbr as Item,
	inf.store_nbr as LocaI,
	case when 
		on_hand_1_qty < 0 
		then 0 
		else on_hand_1_qty 
		end as Stock,
	
	in_transit_qty as IT,
	in_whs_qty as IW,
	on_order_qty as OO,
	zeroifnull(VTA_1Sem) VTA1,
	zeroifnull(VTA_2Sem) VTA2,
	zeroifnull(VTA_3Sem) VTA3,
	zeroifnull(VTA_4Sem) VTA4,
	Ubicación_Comuna,
	Nombre_Empresa,
	Costo_Compra,
	Rcmd_Retail,
	Precio_IVA,	
	
	case when 
		(VTA_1Sem+VTA_2Sem+VTA_3Sem+VTA_4Sem) > 0 
		then Stock /( (VTA_1Sem+VTA_2Sem+VTA_3Sem+VTA_4Sem)*1.00/28)
		else 'SIN VENTA'
		end  DOH	

from k2_wm_vm.inforem_managed_sku inf
	
	left join (
		select item_nbr, store_nbr, sum(wkly_qty) as VTA_1Sem
		from k2_wm_vm.sku_dly_pos 
		where wm_yr_wk = (select wm_yr_wk 
												from k2_wm_vm.calendar_day cal 
												where gregorian_date = DATE-7)
		group by item_nbr, store_nbr
	) vta1 on vta1.item_nbr = inf.item_nbr and vta1.store_nbr = inf.store_nbr
	
	left join (
		select item_nbr, store_nbr, sum(wkly_qty) as VTA_2Sem 
		from k2_wm_vm.sku_dly_pos 
		where wm_yr_wk = (select wm_yr_wk 
												from k2_wm_vm.calendar_day cal 
												where gregorian_date = DATE-7*2)
		group by item_nbr, store_nbr
	) vta2 on vta2.item_nbr = inf.item_nbr and vta2.store_nbr = inf.store_nbr
	
	left join (
		select item_nbr, store_nbr, sum(wkly_qty) as VTA_3Sem 
		from k2_wm_vm.sku_dly_pos 
		where wm_yr_wk = (select wm_yr_wk 
												from k2_wm_vm.calendar_day cal 
												where gregorian_date = DATE-7*3)
		group by item_nbr, store_nbr
	) vta3 on vta3.item_nbr = inf.item_nbr and vta3.store_nbr = inf.store_nbr	
	
	left join (
		select item_nbr, store_nbr, sum(wkly_qty) as VTA_4Sem 
		from k2_wm_vm.sku_dly_pos 
		where wm_yr_wk = (select wm_yr_wk 
												from k2_wm_vm.calendar_day cal 
												where gregorian_date = DATE-7*4)
		group by item_nbr, store_nbr
	) vta4 on vta4.item_nbr = inf.item_nbr and vta4.store_nbr = inf.store_nbr
	
	left join (
		select store_nbr, formato as Nombre_Empresa, comuna as Ubicación_Comuna
		from wm_ad_hoc.locales 
	) lcls on lcls.store_nbr = inf.store_nbr
	
	left join (
		select item_nbr, store_nbr, cost_amt as Costo_Compra, recmd_rtl_amt as Rcmd_Retail, (recmd_rtl_amt*1.19) as Precio_IVA
		from k2_wm_vm.sku_cost_retail
	) cst_retail on cst_retail.store_nbr = inf.store_nbr and cst_retail.item_nbr = inf.item_nbr
	
	left join k2_wm_vm.item it on inf.item_nbr = it.item_nbr
	
sample 10*/ /*where old_nbr = 583253*/

/*order by Stock*/






dia 2 

select
	top 10 VTT_TOTAL,
	dept_nbr as Dpto,
	cast(round(inf.store_nbr,0) as decimal (6,0)  format 'ZZZ') as ID_Local,
	/*
	Formato,
	Tipo_Local as Clasificación_GM,
	Comuna,
	*/
	old_nbr as ID_Producto,
	item1_desc as Producto,
	
	case when 
		on_hand_1_qty < 0 
		then 0 
		else on_hand_1_qty 
		end as Stock,
	
	Precio_Venta,
	Precio_Costo,
	Precio_Venta-Precio_Costo as Beneficio,
	
	in_transit_qty as IT,
	in_whs_qty as IW,
	on_order_qty as OO

/* Venta por semana */
,
	zeroifnull(VTA_1Sem) VTA1,
	VTA1*Precio_Venta as VTA1_TOTAL,
	zeroifnull(VTA_2Sem) VTA2,
	VTA2*Precio_Venta as VTA2_TOTAL,
	zeroifnull(VTA_3Sem) VTA3,
	VTA3*Precio_Venta as VTA3_TOTAL,
	zeroifnull(VTA_4Sem) VTA4,
	VTA4*Precio_Venta as VTA4_TOTAL,
	VTA1+VTA2+VTA3+VTA4 as VTT,
	VTT*Precio_Venta as VTT_TOTAL
	

/*	Venta mensual*/
/*,
	case when 
		(VTA_1Sem+VTA_2Sem+VTA_3Sem+VTA_4Sem) > 0 
		then Stock /( (VTA_1Sem+VTA_2Sem+VTA_3Sem+VTA_4Sem)*1.00/28)
		else 'SIN VENTA'
		end  DOH	
*/

from k2_wm_vm.inforem_managed_sku inf
	
	left join (
		select item_nbr, store_nbr, sum(wkly_qty) as VTA_1Sem
		from k2_wm_vm.sku_dly_pos 
		where wm_yr_wk = (select wm_yr_wk 
												from k2_wm_vm.calendar_day cal 
												where gregorian_date = DATE-7)
		group by item_nbr, store_nbr
	) vta1 on vta1.item_nbr = inf.item_nbr and vta1.store_nbr = inf.store_nbr
	
	left join (
		select item_nbr, store_nbr, sum(wkly_qty) as VTA_2Sem 
		from k2_wm_vm.sku_dly_pos 
		where wm_yr_wk = (select wm_yr_wk 
												from k2_wm_vm.calendar_day cal 
												where gregorian_date = DATE-7*2)
		group by item_nbr, store_nbr
	) vta2 on vta2.item_nbr = inf.item_nbr and vta2.store_nbr = inf.store_nbr
	
	left join (
		select item_nbr, store_nbr, sum(wkly_qty) as VTA_3Sem 
		from k2_wm_vm.sku_dly_pos 
		where wm_yr_wk = (select wm_yr_wk 
												from k2_wm_vm.calendar_day cal 
												where gregorian_date = DATE-7*3)
		group by item_nbr, store_nbr
	) vta3 on vta3.item_nbr = inf.item_nbr and vta3.store_nbr = inf.store_nbr	
	
	left join (
		select item_nbr, store_nbr, sum(wkly_qty) as VTA_4Sem 
		from k2_wm_vm.sku_dly_pos 
		where wm_yr_wk = (select wm_yr_wk 
												from k2_wm_vm.calendar_day cal 
												where gregorian_date = DATE-7*4)
		group by item_nbr, store_nbr
	) vta4 on vta4.item_nbr = inf.item_nbr and vta4.store_nbr = inf.store_nbr
	
	left join (
		select store_nbr, formato as Formato, comuna as Comuna
		from wm_ad_hoc.locales 
	) lcls on lcls.store_nbr = inf.store_nbr
	
	left join (
		select item_nbr, store_nbr, cost_amt as Precio_Costo, recmd_rtl_amt as Precio_Venta_SinIVA, (round(recmd_rtl_amt*1.19,2)) as Precio_Venta
		from k2_wm_vm.sku_cost_retail
	) cst_retail on cst_retail.store_nbr = inf.store_nbr and cst_retail.item_nbr = inf.item_nbr
	
	left join k2_wm_vm.item it on inf.item_nbr = it.item_nbr
	
	left join wm_ad_hoc.compactos_cl cpt on inf.store_nbr = cpt.store_nbr
	
where dept_nbr = 73
/* where dept_nbr in (3, 9, 10, 11, 12, 16, 18, 53, 73) and  Formato in ('LIDER', 'ACUENTA', 'EXPRESS') */
/* order by  Dpto */
/* Filtrar por ID Producto */
/* where ID_Producto = 583253 */

/* Filtrar por local */
/* where ID_Local = 720 */

/* Filtrar por empresa */
/* where Nombre_Empresa = 'Lider' */

/* Producto sin venta mensual (Descomentar DOH)*/
/* where DOH != 'Sin Venta' */
 
/* Filtrar por productos sin Stock */
/* where Stock == 0 */
  
/* Filtrar por productos con Stock */
/* where Stock != 0 */

/* Filtrar por productos con beneficio negativo o con beneficio 0 */
/* where Beneficio <= 0 */
 
/* Filtrar por ubicación */
/* where Ubicación = 'Santiago' */








dia 3 


select 

item1_desc,
dense_rank() over (order by dept_nbr asc) as qwerty,
old_nbr,

sum((zeroifnull(VTA_1Sem)+zeroifnull(VTA_2Sem)+zeroifnull(VTA_3Sem)+zeroifnull(VTA_4Sem))) as VTT,
sum((zeroifnull(VTA_1Sem)+zeroifnull(VTA_2Sem)+zeroifnull(VTA_3Sem)+zeroifnull(VTA_4Sem)))* avg(Precio_Venta_SinIVA)  as VTT_Final

from (
		select dept_nbr, old_nbr, VTA_1Sem,VTA_2Sem, VTA_3Sem, VTA_4Sem, item1_desc,Precio_Venta_SinIVA,
		row_number() over (partition by dept_nbr order by (VTA_1Sem + VTA_2Sem + VTA_3Sem + VTA_4Sem) desc) best
		from  k2_wm_vm.item it
		
		
		left join  k2_wm_vm.inforem_managed_sku inf on inf.item_nbr = it.item_nbr
		
		left join (
					select item_nbr, store_nbr, sum(wkly_qty) as VTA_1Sem
					from k2_wm_vm.sku_dly_pos 
					where wm_yr_wk = (select wm_yr_wk 
													from k2_wm_vm.calendar_day cal 
													where gregorian_date = DATE-7)
					group by item_nbr, store_nbr
					) vta1 on vta1.item_nbr = inf.item_nbr and vta1.store_nbr = inf.store_nbr
				
		left join (
					select item_nbr, store_nbr, sum(wkly_qty) as VTA_2Sem 
					from k2_wm_vm.sku_dly_pos 
					where wm_yr_wk = (select wm_yr_wk 
													from k2_wm_vm.calendar_day cal 
													where gregorian_date = DATE-7*2)
					group by item_nbr, store_nbr
					) vta2 on vta2.item_nbr = inf.item_nbr and vta2.store_nbr = inf.store_nbr
		
		left join (
					select item_nbr, store_nbr, sum(wkly_qty) as VTA_3Sem 
					from k2_wm_vm.sku_dly_pos 
					where wm_yr_wk = (select wm_yr_wk 
													from k2_wm_vm.calendar_day cal 
													where gregorian_date = DATE-7*3)
					group by item_nbr, store_nbr
					) vta3 on vta3.item_nbr = inf.item_nbr and vta3.store_nbr = inf.store_nbr	
		
		left join (
					select item_nbr, store_nbr, sum(wkly_qty) as VTA_4Sem 
					from k2_wm_vm.sku_dly_pos 
					where wm_yr_wk = (select wm_yr_wk 
													from k2_wm_vm.calendar_day cal 
													where gregorian_date = DATE-7*4)
					group by item_nbr, store_nbr	
					) vta4 on vta4.item_nbr = inf.item_nbr and vta4.store_nbr = inf.store_nbr
		
		left join (
					select item_nbr, store_nbr, cost_amt as Precio_Costo, recmd_rtl_amt as Precio_Venta_SinIVA, (round(recmd_rtl_amt*1.19,2)) as Precio_Venta
					from k2_wm_vm.sku_cost_retail
					) cst_retail on cst_retail.store_nbr = inf.store_nbr and cst_retail.item_nbr = inf.item_nbr
		
							
		) tito

where best < 5
group by  old_nbr, item1_desc, dept_nbr
order by qwerty asc, VTT_Final desc







boton excel dia 4


Sub Boton()
    'Declarando las variables
    Dim item As Variant
    Dim strConn As String
    Dim item2 As Variant
    'Pedimos por pantalla ingresar un datos
    item = InputBox("Ingrese el item a buscar", "Item Table")
    item2 = InputBox("Ingrese el nª local", "Inforem Table")
    
    'Declaramos la variable para conectar como string
    Dim connection As String
    
    'Declaramos un objeto de conexion
    Dim cnDB As New ADODB.connection 'En caso de error activar en Tools/References/Microsoft ActiveX Data Objects 2.5 Library
    
    'Declaramos un objeto recordset
    Dim rsRecords As New ADODB.Recordset

    'Abrimos la conexion ODBC
    cnDB.Open "WMG"
    
    'Creamos la query
    rsRecords.Open "Select item1_desc k2_wm_vm.item where old_nbr=" & item, cnDB

    'Declaramos una variable
    Dim desc As String
   
    'Guardamos el resultado obtenido en la variable desc
    desc = rsRecords.Fields("item1_desc").Value
    
    'Mostramos por pantalla el resultado
    MsgBox (desc)

    'Cerramos todo y dejamos seteado las referencias por defecto con nada
    rsRecords.Close
    Set rsRecords = Nothing
    cnDB.Close
    Set cnDB = Nothing
End Sub






dia 4 , otra funcion excel macro


Sub Boton()

    Consulta.Show
    
End Sub

Sub QuerySql(item, tienda)
    'Declarando las variables
    Dim strConn As String
    'Pedimos por pantalla ingresar un datos
    'ITEM = InputBox("Ingrese el item a buscar", "Item Table")
    'depto = InputBox("Ingrese el depto asociado", "Item Table")
    'tienda = InputBox("Ingrese la tienda asociada", "Item Table")
  
    
'    item = Consulta.TextBox1.Value
'    MsgBox (item)

'    buscar cancelar el proceso si se pone cancelar!

'    Declaramos la variable para conectar como string
    Dim connection As String

'    Declaramos un objeto de conexion
    Dim cnDB As New ADODB.connection 'En caso de error activar en Tools/References/Microsoft ActiveX Data Objects 2.5 Library

'    Declaramos un objeto recordset
   Dim rsRecords As New ADODB.Recordset

'    Abrimos la conexion ODBC
    cnDB.Open "WMG"

'    Creamos la query
    rsRecords.Open "select inf.on_hand_1_qty from k2_wm_vm.item it " & _
                    "left join k2_wm_vm.inforem_managed_sku inf " & _
                    "on it.item_nbr = inf.item_nbr " & _
                    "where old_nbr = " & item & " and store_nbr = " & tienda & "", cnDB


'    Declaramos una variable
    Dim Resultado As String

'    Guardamos el resultado obtenido en la variable desc
    Resultado = rsRecords.Fields("on_hand_1_qty").Value

'    Mostramos por pantalla el resultado
    MsgBox (Resultado)

'    Cerramos todo y dejamos seteado las referencias por defecto con nada
    rsRecords.Close
    Set rsRecords = Nothing
    cnDB.Close
    Set cnDB = Nothing
End Sub





top 5 productos mas vendidos por depto 



--terminado el top 5
select 

item1_desc as ITEM,
dept_nbr as DEPTO,
old_nbr as LocaI,
r0w as TOPs,

sum((zeroifnull(VTA_1Sem)+zeroifnull(VTA_2Sem)+zeroifnull(VTA_3Sem)+zeroifnull(VTA_4Sem))) as VTT,
sum((zeroifnull(VTA_1Sem)+zeroifnull(VTA_2Sem)+zeroifnull(VTA_3Sem)+zeroifnull(VTA_4Sem)))* avg(Precio_Venta_SinIVA)  as VTT_Final

from (
		select dept_nbr, old_nbr, VTA_1Sem,VTA_2Sem, VTA_3Sem, VTA_4Sem, item1_desc,Precio_Venta_SinIVA,
		row_number() over (partition by dept_nbr order by zeroifnull(VTA_1Sem)+zeroifnull(VTA_2Sem)+zeroifnull(VTA_3Sem)+zeroifnull(VTA_4Sem) desc) r0w
		from  k2_wm_vm.item it
		
		
		left join  k2_wm_vm.inforem_managed_sku inf on inf.item_nbr = it.item_nbr
		
		left join (
					select item_nbr, store_nbr, sum(wkly_qty) as VTA_1Sem
					from k2_wm_vm.sku_dly_pos 
					where wm_yr_wk = (select wm_yr_wk 
													from k2_wm_vm.calendar_day cal 
													where gregorian_date = DATE-7)
					group by item_nbr, store_nbr
					) vta1 on vta1.item_nbr = inf.item_nbr and vta1.store_nbr = inf.store_nbr
				
		left join (
					select item_nbr, store_nbr, sum(wkly_qty) as VTA_2Sem 
					from k2_wm_vm.sku_dly_pos 
					where wm_yr_wk = (select wm_yr_wk 
													from k2_wm_vm.calendar_day cal 
													where gregorian_date = DATE-7*2)
					group by item_nbr, store_nbr
					) vta2 on vta2.item_nbr = inf.item_nbr and vta2.store_nbr = inf.store_nbr
		
		left join (
					select item_nbr, store_nbr, sum(wkly_qty) as VTA_3Sem 
					from k2_wm_vm.sku_dly_pos 
					where wm_yr_wk = (select wm_yr_wk 
													from k2_wm_vm.calendar_day cal 
													where gregorian_date = DATE-7*3)
					group by item_nbr, store_nbr
					) vta3 on vta3.item_nbr = inf.item_nbr and vta3.store_nbr = inf.store_nbr	
		
		left join (
					select item_nbr, store_nbr, sum(wkly_qty) as VTA_4Sem 
					from k2_wm_vm.sku_dly_pos 
					where wm_yr_wk = (select wm_yr_wk 
													from k2_wm_vm.calendar_day cal 
													where gregorian_date = DATE-7*4)
					group by item_nbr, store_nbr	
					) vta4 on vta4.item_nbr = inf.item_nbr and vta4.store_nbr = inf.store_nbr
		
		left join (
					select item_nbr, store_nbr, cost_amt as Precio_Costo, recmd_rtl_amt as Precio_Venta_SinIVA, (round(recmd_rtl_amt*1.19,2)) as Precio_Venta
					from k2_wm_vm.sku_cost_retail
					) cst_retail on cst_retail.store_nbr = inf.store_nbr and cst_retail.item_nbr = inf.item_nbr
		
							
		) tito

where r0w < 6 
group by  old_nbr, item1_desc, dept_nbr, r0w
order by DEPTO asc, r0w asc










solicitud

select 
dept_nbr as DEPTO,
old_nbr as ITEM,
store_nbr as L0CAL,
mbm_code as MBM,
carry_option as CARRY_OPTION,
carried_status as  CARRIED_STATUS,
origen as ORIGEN,
item_status_code as ITEM_STATUS,
item_type_code as ITEM_TYPE

from k2_wm_vm.item it

left join k2_wm_vm.inforem_managed_sku inf on it.item_nbr = inf.item_nbr

left join wm_ad_hoc.vendors vr on it.vendor_nbr =vr. vndr_nbr

where dept_nbr in (3,9,10,11,12,16,53,73) and carry_option = 'R' and carried_status = 'R' and MBM in ( 'M', 'H', 'P')
order by dept_nbr







full query 

SELECT	
T2.WHSE_NBR,
T2.PO_NBR,
T2.PO_STATUS,
T2.STEP_STATUS,
T2.EVENT_DESC,
T2.PO_TYPE, 
T2.ORDER_DEPT_NBR,
T2.VENDOR_NBR,
VT.VNDR_NAME,
T2.VENDOR_NBR_SEQ,
T1.OLD_NBR(NAMED"ITEM"),
T1.ITEM_STATUS_CODE(NAMED"ITEM STATUS"),
T1.ITEM_RPLNSHBL_IND(NAMED"OB"),
T1.CANCEL_WHN_OUT_IND(NAMED"CWO"),
T1.MBM_CODE(NAMED"MBM"),
T1.REPL_SUBTYPE_CODE(NAMED"SUB-TIPO"),
T2.BUYER_NAME,
T2.LAST_CHG_INIT AS "SIGLA ULTIMO CAMBIO",
T2.ENTRY_COMP_INIT AS "SIGLA ENTRY",
T2.ROUT_INIT AS "SIGLA ROUT",
T2.AUTH_INIT AS "SIGLA AUTORIZACION",
T2.ORDER_DATE(NAMED"FECHA DE CREACIÓN"), 
T2.CANCEL_DATE(NAMED"FECHA DE VENCIMIENTO"),
WEEKNUMBER_OF_YEAR (T2.CANCEL_DATE, 'ISO') (NAMED"SEMANA"),
SUM((T4.WHPK_QTY_RCVD*T1.WHPK_QTY)/T1.VNPK_QTY)(NAMED"CAJAS RECIBIDAS"),
SUM((T4.WHPK_ORDER*T1.WHPK_QTY)/T1.VNPK_QTY)(NAMED"CAJAS ORDENADAS"),
"CAJAS ORDENADAS"-"CAJAS RECIBIDAS" AS "CAJAS NO ENTREGADAS",
T5.BRAND_NAME,
T1.ITEM1_DESC,
T1.VNPK_COST_AMT*100*"CAJAS NO ENTREGADAS"(NAMED"COSTO CAJA NO ENTREGADA")
,TRIM(DIM.DEPT_CATEGORY_DESC)(NAMED"CATEGORIA")
,TRIM(DIM.DEPT_SUBCATG_DESC)(NAMED"SUB CATEGORIA")
,TRIM(DIM.FINELINE_DESC)(NAMED"FINELINE")

FROM	
K2_WM_VM.PURCHASE_ORDER T2,
K2_WM_VM.PO_LINE T4

LEFT JOIN K2_WM_VM.ITEM T1 ON T1.ITEM_NBR = T4.ITEM_NBR
LEFT JOIN WW_MDSE_DM_VM.FINELINE_DIM DIM ON DIM.COUNTRY_CODE='K2' AND DIM.CURRENT_IND='Y' AND T1.FINELINE_NBR=DIM.FINELINE_NBR AND T1.DEPT_NBR=DIM.DEPT_NBR
LEFT JOIN K2_WM_VM.BRAND T5 ON T1.BRAND_ID = T5.BRAND_ID
LEFT JOIN K2_WM_VM.VENDOR_MASTER VT ON VT.VNDR_NBR = T1.VENDOR_NBR
LEFT JOIN WM_AD_HOC.VENDORS VNO ON VNO.VNDR_NBR = T1.VENDOR_NBR

WHERE	

T2.EVENT_DESC NOT IN ('ERROR') 
    AND   T2.PO_NBR=T4.PO_NBR 
    AND   T2.ORDER_DEPT_NBR NOT IN (66) 
    AND    T1.STORE_FORMAT_CODE  IN (1) 
    AND    T1.SHLFLBL1_COLR_DESC  NOT IN ('MAY') 
    AND   T2.STEP_STATUS NOT IN ('E', 'L', 'M', 'N') 
AND    T2.ORDER_DEPT_NBR  IN (3,9,10,11,12,16,18,53,73)
    AND   VNO.ORIGEN IN ('NACIONAL')
    AND   T2.CANCEL_DATE BETWEEN  DATE-7*5 AND DATE-1
GROUP	BY

T2.WHSE_NBR,
T2.PO_NBR,
T2.PO_STATUS,
T2.STEP_STATUS,
T2.EVENT_DESC,
T2.PO_TYPE, 
T2.ORDER_DEPT_NBR,
T2.VENDOR_NBR,
VT.VNDR_NAME,
T2.VENDOR_NBR_SEQ,
T1.OLD_NBR(NAMED"ITEM"),
T1.MBM_CODE,
T1.ITEM_STATUS_CODE(NAMED"ITEM STATUS"),
T1.ITEM_RPLNSHBL_IND,
T1.REPL_SUBTYPE_CODE,
T1.CANCEL_WHN_OUT_IND(NAMED"CWO"),
T2.BUYER_NAME,
T2.LAST_CHG_INIT,
T2.ENTRY_COMP_INIT,
T2.ROUT_INIT,
T2.AUTH_INIT ,
T2.ORDER_DATE(NAMED"FECHA DE CREACIÓN"), 
T2.CANCEL_DATE(NAMED"FECHA DE VENCIMIENTO"),
T4.WHPK_QTY_RCVD,
T1.WHPK_QTY,
T1.VNPK_QTY,
T4.WHPK_ORDER,
T1.VNPK_QTY,
T5.BRAND_NAME,
T1.ITEM1_DESC,
T1.VNPK_COST_AMT,
DIM.DEPT_CATEGORY_DESC,
DIM.DEPT_SUBCATG_DESC,
DIM.FINELINE_DESC




