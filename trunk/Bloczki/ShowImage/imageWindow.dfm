object imgWindow: TimgWindow
  Left = 0
  Top = 0
  Caption = 'imgWindow'
  ClientHeight = 259
  ClientWidth = 375
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 13
  object Panel: TPanel
    Left = 0
    Top = 0
    Width = 375
    Height = 259
    Align = alClient
    TabOrder = 0
    object ScrollBoxPicture: TScrollBox
      Left = 104
      Top = 8
      Width = 265
      Height = 241
      HorzScrollBar.Tracking = True
      VertScrollBar.Tracking = True
      TabOrder = 0
      object ImagePicture: TImage
        Left = 0
        Top = 0
        Width = 105
        Height = 105
        OnMouseMove = ImagePictureMouseMove
      end
    end
    object ScrollBoxPicsels: TScrollBox
      Left = 0
      Top = 8
      Width = 98
      Height = 241
      TabOrder = 1
      object LabelSizeText: TLabel
        Left = 5
        Top = 5
        Width = 42
        Height = 13
        Caption = 'Wymiary'
      end
      object LabelSize: TLabel
        Left = 5
        Top = 24
        Width = 26
        Height = 13
        Caption = '0 '#215' 0'
      end
      object LabelX: TLabel
        Left = 5
        Top = 64
        Width = 6
        Height = 13
        Caption = 'X'
      end
      object LabelY: TLabel
        Left = 5
        Top = 91
        Width = 6
        Height = 13
        Caption = 'Y'
      end
      object ImageSquare: TImage
        Left = 17
        Top = 115
        Width = 48
        Height = 46
      end
      object LabelR: TLabel
        Left = 5
        Top = 176
        Width = 7
        Height = 13
        Caption = 'R'
      end
      object LabelG: TLabel
        Left = 5
        Top = 195
        Width = 7
        Height = 13
        Caption = 'G'
      end
      object LabelB: TLabel
        Left = 5
        Top = 214
        Width = 6
        Height = 13
        Caption = 'B'
      end
      object EditX: TEdit
        Left = 17
        Top = 61
        Width = 48
        Height = 21
        TabOrder = 0
        Text = '0'
        OnChange = EditXChange
        OnKeyPress = EditXKeyPress
      end
      object EditY: TEdit
        Left = 17
        Top = 88
        Width = 48
        Height = 21
        TabOrder = 1
        Text = '0'
        OnChange = EditYChange
        OnKeyPress = EditYKeyPress
      end
    end
  end
end
